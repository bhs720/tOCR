#include "mupdf\fitz.h"
#include "tiff\tiffio.h"

typedef struct fz_extract_device_s
{
	fz_device super;
	fz_output *out;
	int imagecount;
	int pagenum;
	TIFF *tif;
	char *filename;
	char *output_base;
} fz_extract_device;

static char compression_name[][8] =
{
	"Unknown",
	"Raw",
	"Fax",
	"Flate",
	"LZW",
	"RLD",
	"BMP",
	"GIF",
	"JPEG",
	"JPX",
	"JXR",
	"PNG",
	"PNM",
	"TIFF"
};

static void
fz_extract_fill_image(fz_context *ctx, fz_device *dev, fz_image *image, const fz_matrix *ctm, float alpha, const fz_color_params *color_params)
{
	fz_extract_device *ex = (fz_extract_device*)dev;
	ex->imagecount++;
	fz_output *out = ((fz_extract_device*)dev)->out;
	enum fz_colorspace_type cstype;
	cstype = fz_colorspace_type(ctx, image->colorspace);
	const char *csname = fz_colorspace_name(ctx, image->colorspace);
	
	double ptWidth = ctm->a - ctm->e;
	double ptHeight = ctm->d - ctm->f;
	double inWidth = ptWidth / 72.0;
	double inHeight = ptHeight / 72.0;
	int xdpi = (int)(image->w / inWidth + 0.5);
	int ydpi = (int)(image->h / inHeight + 0.5);

	unsigned char *data = NULL;
	fz_compressed_buffer *buff = fz_compressed_image_buffer(ctx, image);
	
	fz_write_printf(ctx, out, "page=%d img=%d wpx=%d hpx=%d win=%f hin=%f xres=%d yres=%d bpc=%d spp=%d cs=%s comp=%s\r\n",
		ex->pagenum + 1, ex->imagecount, image->w, image->h, inWidth, inHeight, xdpi, ydpi, image->bpc, image->n, csname, compression_name[buff->params.type]);
	
	unsigned char *buffer_data;
	size_t buffer_length = fz_buffer_storage(ctx, buff->buffer, &buffer_data);

	char filepath[255];
	sprintf(filepath, "%s\\%s-%03d-%03d.tif", ex->output_base, ex->filename, ex->pagenum + 1, ex->imagecount);
	ex->tif = TIFFOpen(filepath, "w");

	TIFFSetField(ex->tif, TIFFTAG_IMAGEWIDTH, image->w);
	TIFFSetField(ex->tif, TIFFTAG_IMAGELENGTH, image->h);
	TIFFSetField(ex->tif, TIFFTAG_BITSPERSAMPLE, image->bpc);
	TIFFSetField(ex->tif, TIFFTAG_ROWSPERSTRIP, image->h);
	TIFFSetField(ex->tif, TIFFTAG_SAMPLESPERPIXEL, image->n);
	TIFFSetField(ex->tif, TIFFTAG_PLANARCONFIG, PLANARCONFIG_CONTIG);
	TIFFSetField(ex->tif, TIFFTAG_RESOLUTIONUNIT, RESUNIT_INCH);
	TIFFSetField(ex->tif, TIFFTAG_XRESOLUTION, (float)xdpi);
	TIFFSetField(ex->tif, TIFFTAG_YRESOLUTION, (float)ydpi);

	if (image->n == 1)
		TIFFSetField(ex->tif, TIFFTAG_PHOTOMETRIC, PHOTOMETRIC_MINISBLACK);
	if (image->n == 3 && image->bpc == 8)
		TIFFSetField(ex->tif, TIFFTAG_PHOTOMETRIC, PHOTOMETRIC_RGB);

	switch (buff->params.type)
	{	
	case FZ_IMAGE_UNKNOWN:
	case FZ_IMAGE_RAW:
		TIFFSetField(ex->tif, TIFFTAG_COMPRESSION, COMPRESSION_NONE);
		break;
	case FZ_IMAGE_FAX:
		TIFFSetField(ex->tif, TIFFTAG_COMPRESSION, COMPRESSION_CCITT_T6);
		//if (buff->params.u.fax.black_is_1)
			TIFFSetField(ex->tif, TIFFTAG_PHOTOMETRIC, PHOTOMETRIC_MINISWHITE);
		break;
	case FZ_IMAGE_FLATE:
		TIFFSetField(ex->tif, TIFFTAG_COMPRESSION, COMPRESSION_DEFLATE);
		if (buff->params.u.flate.predictor == 2)
			TIFFSetField(ex->tif, TIFFTAG_PREDICTOR, PREDICTOR_HORIZONTAL);
		else
			TIFFSetField(ex->tif, TIFFTAG_PREDICTOR, PREDICTOR_NONE);
		break;
	case FZ_IMAGE_LZW:
		TIFFSetField(ex->tif, TIFFTAG_COMPRESSION, COMPRESSION_LZW);
		if (buff->params.u.lzw.predictor == 2)
			TIFFSetField(ex->tif, TIFFTAG_PREDICTOR, PREDICTOR_HORIZONTAL);
		break;
	case FZ_IMAGE_RLD:
		TIFFSetField(ex->tif, TIFFTAG_COMPRESSION, COMPRESSION_PACKBITS);
		break;
	case FZ_IMAGE_JPEG:
		TIFFSetField(ex->tif, TIFFTAG_COMPRESSION, COMPRESSION_JPEG);
		if (image->n == 3)
			TIFFSetField(ex->tif, TIFFTAG_PHOTOMETRIC, PHOTOMETRIC_YCBCR);
		break;
	case FZ_IMAGE_BMP:
	case FZ_IMAGE_GIF:
	case FZ_IMAGE_JPX:
	case FZ_IMAGE_JXR:
	case FZ_IMAGE_PNG:
	case FZ_IMAGE_PNM:
	case FZ_IMAGE_TIFF:
	default:
		break;
	}
	
	tmsize_t size_written = TIFFWriteRawStrip(ex->tif, 0, buffer_data, buffer_length);
	TIFFClose(ex->tif);
}

fz_device *fz_new_extract_device(fz_context *ctx, int pagenum, fz_output *out, char *output_base, char *filename)
{
	fz_extract_device *dev = fz_new_derived_device(ctx, fz_extract_device);
	
	dev->super.fill_image = fz_extract_fill_image;

	dev->out = out;
	dev->pagenum = pagenum;
	dev->output_base = output_base;
	dev->filename = filename;

	return (fz_device*)dev;
}
