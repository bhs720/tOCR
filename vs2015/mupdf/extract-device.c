#include "mupdf/fitz.h"

typedef struct fz_extract_device_s
{
	fz_device super;
	fz_output *out;
	int imagecount;
	int pagenum;
} fz_extract_device;

static void
fz_extract_matrix(fz_context *ctx, fz_output *out, const fz_matrix *ctm)
{
	//fz_write_printf(ctx, out, " matrix=\"%g %g %g %g %g %g\"",
	//	ctm->a, ctm->b, ctm->c, ctm->d, ctm->e, ctm->f);
}

static void
fz_extract_color(fz_context *ctx, fz_output *out, fz_colorspace *colorspace, const float *color, float alpha)
{
	//int i, n;
	//if (colorspace)
	//{
	//	n = fz_colorspace_n(ctx, colorspace);
	//	fz_write_printf(ctx, out, " colorspace=\"%s\" color=\"", fz_colorspace_name(ctx, colorspace));
	//	for (i = 0; i < n; i++)
	//		fz_write_printf(ctx, out, "%s%g", i == 0 ? "" : " ", color[i]);
	//	fz_write_printf(ctx, out, "\"");
	//}
	//if (alpha < 1)
	//	fz_write_printf(ctx, out, " alpha=\"%g\"", alpha);
}

static int
isxmlmeta(int c)
{
	return c < 32 || c >= 128 || c == '&' || c == '<' || c == '>' || c == '\'' || c == '"';
}

static void
fz_extract_text_span(fz_context *ctx, fz_output *out, fz_text_span *span)
{
	//int i;
	//fz_write_printf(ctx, out, "<span font=\"%s\" wmode=\"%d\" bidi=\"%d\"", fz_font_name(ctx, span->font), span->wmode, span->bidi_level);
	//fz_write_printf(ctx, out, " trm=\"%g %g %g %g\">\n", span->trm.a, span->trm.b, span->trm.c, span->trm.d);
	//for (i = 0; i < span->len; i++)
	//{
	//	char name[32];

	//	if (span->items[i].ucs == -1)
	//		fz_write_printf(ctx, out, "<g unicode=\"-1\"");
	//	else if (!isxmlmeta(span->items[i].ucs))
	//		fz_write_printf(ctx, out, "<g unicode=\"%c\"", span->items[i].ucs);
	//	else
	//		fz_write_printf(ctx, out, "<g unicode=\"U+%04x\"", span->items[i].ucs);

	//	if (span->items[i].gid >= 0)
	//	{
	//		fz_get_glyph_name(ctx, span->font, span->items[i].gid, name, sizeof name);
	//		fz_write_printf(ctx, out, " glyph=\"%s\"", name);
	//	}
	//	else
	//		fz_write_printf(ctx, out, " glyph=\"-1\"");

	//	fz_write_printf(ctx, out, " x=\"%g\" y=\"%g\" />\n", span->items[i].x, span->items[i].y);
	//}
	//fz_write_printf(ctx, out, "</span>\n");
}

static void
fz_extract_text(fz_context *ctx, fz_output *out, const fz_text *text)
{
	//fz_text_span *span;
	//for (span = text->head; span; span = span->next)
	//	fz_extract_text_span(ctx, out, span);
}

static void
extract_moveto(fz_context *ctx, void *arg, float x, float y)
{
	//fz_output *out = arg;
	//fz_write_printf(ctx, out, "<moveto x=\"%g\" y=\"%g\"/>\n", x, y);
}

static void
extract_lineto(fz_context *ctx, void *arg, float x, float y)
{
	//fz_output *out = arg;
	//fz_write_printf(ctx, out, "<lineto x=\"%g\" y=\"%g\"/>\n", x, y);
}

static void
extract_curveto(fz_context *ctx, void *arg, float x1, float y1, float x2, float y2, float x3, float y3)
{
	//fz_output *out = arg;
	//fz_write_printf(ctx, out, "<curveto x1=\"%g\" y1=\"%g\" x2=\"%g\" y2=\"%g\" x3=\"%g\" y3=\"%g\"/>\n", x1, y1, x2, y2, x3, y3);
}

static void
extract_close(fz_context *ctx, void *arg)
{
	//fz_output *out = arg;
	//fz_write_printf(ctx, out, "<closepath/>\n");
}

static const fz_path_walker extract_path_walker =
{
	extract_moveto,
	extract_lineto,
	extract_curveto,
	extract_close
};

static void
fz_extract_path(fz_context *ctx, fz_output *out, const fz_path *path)
{
	//fz_walk_path(ctx, path, &extract_path_walker, out);
}

static void
fz_extract_fill_path(fz_context *ctx, fz_device *dev, const fz_path *path, int even_odd, const fz_matrix *ctm,
	fz_colorspace *colorspace, const float *color, float alpha, const fz_color_params *color_params)
{
	//fz_output *out = ((fz_extract_device*)dev)->out;
	//fz_write_printf(ctx, out, "<fill_path");
	//if (even_odd)
	//	fz_write_printf(ctx, out, " winding=\"eofill\"");
	//else
	//	fz_write_printf(ctx, out, " winding=\"nonzero\"");
	//fz_extract_color(ctx, out, colorspace, color, alpha);
	//fz_extract_matrix(ctx, out, ctm);
	//fz_write_printf(ctx, out, ">\n");
	//fz_extract_path(ctx, out, path);
	//fz_write_printf(ctx, out, "</fill_path>\n");
}

static void
fz_extract_stroke_path(fz_context *ctx, fz_device *dev, const fz_path *path, const fz_stroke_state *stroke, const fz_matrix *ctm,
	fz_colorspace *colorspace, const float *color, float alpha, const fz_color_params *color_params)
{
	//fz_output *out = ((fz_extract_device*)dev)->out;
	//int i;

	//fz_write_printf(ctx, out, "<stroke_path");
	//fz_write_printf(ctx, out, " linewidth=\"%g\"", stroke->linewidth);
	//fz_write_printf(ctx, out, " miterlimit=\"%g\"", stroke->miterlimit);
	//fz_write_printf(ctx, out, " linecap=\"%d,%d,%d\"", stroke->start_cap, stroke->dash_cap, stroke->end_cap);
	//fz_write_printf(ctx, out, " linejoin=\"%d\"", stroke->linejoin);

	//if (stroke->dash_len)
	//{
	//	fz_write_printf(ctx, out, " dash_phase=\"%g\" dash=\"", stroke->dash_phase);
	//	for (i = 0; i < stroke->dash_len; i++)
	//		fz_write_printf(ctx, out, "%s%g", i > 0 ? " " : "", stroke->dash_list[i]);
	//	fz_write_printf(ctx, out, "\"");
	//}

	//fz_extract_color(ctx, out, colorspace, color, alpha);
	//fz_extract_matrix(ctx, out, ctm);
	//fz_write_printf(ctx, out, ">\n");

	//fz_extract_path(ctx, out, path);

	//fz_write_printf(ctx, out, "</stroke_path>\n");
}

static void
fz_extract_clip_path(fz_context *ctx, fz_device *dev, const fz_path *path, int even_odd, const fz_matrix *ctm, const fz_rect *scissor)
{
	//fz_output *out = ((fz_extract_device*)dev)->out;
	//fz_write_printf(ctx, out, "<clip_path");
	//if (even_odd)
	//	fz_write_printf(ctx, out, " winding=\"eofill\"");
	//else
	//	fz_write_printf(ctx, out, " winding=\"nonzero\"");
	//fz_extract_matrix(ctx, out, ctm);
	//fz_write_printf(ctx, out, ">\n");
	//fz_extract_path(ctx, out, path);
	//fz_write_printf(ctx, out, "</clip_path>\n");
}

static void
fz_extract_clip_stroke_path(fz_context *ctx, fz_device *dev, const fz_path *path, const fz_stroke_state *stroke, const fz_matrix *ctm, const fz_rect *scissor)
{
	//fz_output *out = ((fz_extract_device*)dev)->out;
	//fz_write_printf(ctx, out, "<clip_stroke_path");
	//fz_extract_matrix(ctx, out, ctm);
	//fz_write_printf(ctx, out, ">\n");
	//fz_extract_path(ctx, out, path);
	//fz_write_printf(ctx, out, "</clip_stroke_path>\n");
}

static void
fz_extract_fill_text(fz_context *ctx, fz_device *dev, const fz_text *text, const fz_matrix *ctm,
	fz_colorspace *colorspace, const float *color, float alpha, const fz_color_params *color_params)
{
	//fz_output *out = ((fz_extract_device*)dev)->out;
	//fz_write_printf(ctx, out, "<fill_text");
	//fz_extract_color(ctx, out, colorspace, color, alpha);
	//fz_extract_matrix(ctx, out, ctm);
	//fz_write_printf(ctx, out, ">\n");
	//fz_extract_text(ctx, out, text);
	//fz_write_printf(ctx, out, "</fill_text>\n");
}

static void
fz_extract_stroke_text(fz_context *ctx, fz_device *dev, const fz_text *text, const fz_stroke_state *stroke, const fz_matrix *ctm,
	fz_colorspace *colorspace, const float *color, float alpha, const fz_color_params *color_params)
{
	//fz_output *out = ((fz_extract_device*)dev)->out;
	//fz_write_printf(ctx, out, "<stroke_text");
	//fz_extract_color(ctx, out, colorspace, color, alpha);
	//fz_extract_matrix(ctx, out, ctm);
	//fz_write_printf(ctx, out, ">\n");
	//fz_extract_text(ctx, out, text);
	//fz_write_printf(ctx, out, "</stroke_text>\n");
}

static void
fz_extract_clip_text(fz_context *ctx, fz_device *dev, const fz_text *text, const fz_matrix *ctm, const fz_rect *scissor)
{
	//fz_output *out = ((fz_extract_device*)dev)->out;
	//fz_write_printf(ctx, out, "<clip_text");
	//fz_extract_matrix(ctx, out, ctm);
	//fz_write_printf(ctx, out, ">\n");
	//fz_extract_text(ctx, out, text);
	//fz_write_printf(ctx, out, "</clip_text>\n");
}

static void
fz_extract_clip_stroke_text(fz_context *ctx, fz_device *dev, const fz_text *text, const fz_stroke_state *stroke, const fz_matrix *ctm, const fz_rect *scissor)
{
	//fz_output *out = ((fz_extract_device*)dev)->out;
	//fz_write_printf(ctx, out, "<clip_stroke_text");
	//fz_extract_matrix(ctx, out, ctm);
	//fz_write_printf(ctx, out, ">\n");
	//fz_extract_text(ctx, out, text);
	//fz_write_printf(ctx, out, "</clip_stroke_text>\n");
}

static void
fz_extract_ignore_text(fz_context *ctx, fz_device *dev, const fz_text *text, const fz_matrix *ctm)
{
	//fz_output *out = ((fz_extract_device*)dev)->out;
	//fz_write_printf(ctx, out, "<ignore_text");
	//fz_extract_matrix(ctx, out, ctm);
	//fz_write_printf(ctx, out, ">\n");
	//fz_extract_text(ctx, out, text);
	//fz_write_printf(ctx, out, "</ignore_text>\n");
}

static void
fz_extract_fill_image(fz_context *ctx, fz_device *dev, fz_image *image, const fz_matrix *ctm, float alpha, const fz_color_params *color_params)
{
	fz_extract_device *ex = (fz_extract_device*)dev;
	ex->imagecount++;
	fz_output *out = ((fz_extract_device*)dev)->out;
	enum fz_colorspace_type cstype;
	cstype = fz_colorspace_type(ctx, image->colorspace);
	char *csname = fz_colorspace_name(ctx, image->colorspace);

	double ptWidth = ctm->a - ctm->e;
	double ptHeight = ctm->d - ctm->f;
	double inWidth = ptWidth / 72.0;
	double inHeight = ptHeight / 72.0;
	int xdpi = (int)(image->w / inWidth + 0.5);
	int ydpi = (int)(image->h / inHeight + 0.5);

	char *compname = "";
	unsigned char *data = NULL;
	fz_compressed_buffer *buff = fz_compressed_image_buffer(ctx, image);
	switch (buff->params.type)
	{
	case FZ_IMAGE_UNKNOWN:
		compname = "Unknown";
		break;

		/* Uncompressed samples */
	case FZ_IMAGE_RAW:
		compname = "RAW";
		break;

		/* Compressed samples */
	case FZ_IMAGE_FAX:
		compname = "FAX";
		break;
	case FZ_IMAGE_FLATE:
		compname = "FLATE";
		break;
	case FZ_IMAGE_LZW:
		compname = "LZW";
		break;
	case FZ_IMAGE_RLD:
		compname = "RLD";
		break;

		/* Full image formats */
	case FZ_IMAGE_BMP:
		compname = "BMP";
		break;
	case FZ_IMAGE_GIF:
		compname = "GIF";
		break;
	case FZ_IMAGE_JPEG:
		compname = "JPEG";
		break;
	case FZ_IMAGE_JPX:
		compname = "JPX";
		break;
	case FZ_IMAGE_JXR:
		compname = "JXR";
		break;
	case FZ_IMAGE_PNG:
		compname = "PNG";
		break;
	case FZ_IMAGE_PNM:
		compname = "PNM";
		break;
	case FZ_IMAGE_TIFF:
		compname = "TIFF";
		break;
	default:
		compname = "Unknown";
		break;
	}
	size_t len = fz_buffer_storage(ctx, buff->buffer, &data);

	fz_write_printf(ctx, out, "page=%d img=%d wpx=%d hpx=%d win=%f hin=%f xres=%d yres=%d bpc=%d spp=%d cs=%s comp=%s\r\n", ex->pagenum + 1, ex->imagecount, image->w, image->h, inWidth, inHeight, xdpi, ydpi, image->bpc, image->n, csname, compname);

}

static void
fz_extract_fill_shade(fz_context *ctx, fz_device *dev, fz_shade *shade, const fz_matrix *ctm, float alpha, const fz_color_params *color_params)
{
	/*fz_output *out = ((fz_extract_device*)dev)->out;
	fz_write_printf(ctx, out, "<fill_shade alpha=\"%g\"", alpha);
	fz_extract_matrix(ctx, out, ctm);
	fz_write_printf(ctx, out, "/>\n");*/
}

static void
fz_extract_fill_image_mask(fz_context *ctx, fz_device *dev, fz_image *image, const fz_matrix *ctm,
	fz_colorspace *colorspace, const float *color, float alpha, const fz_color_params *color_params)
{
	/*fz_output *out = ((fz_extract_device*)dev)->out;
	fz_write_printf(ctx, out, "<fill_image_mask");
	fz_extract_matrix(ctx, out, ctm);
	fz_extract_color(ctx, out, colorspace, color, alpha);
	fz_write_printf(ctx, out, " width=\"%d\" height=\"%d\"", image->w, image->h);
	fz_write_printf(ctx, out, "/>\n");*/
}

static void
fz_extract_clip_image_mask(fz_context *ctx, fz_device *dev, fz_image *image, const fz_matrix *ctm, const fz_rect *scissor)
{
	/*fz_output *out = ((fz_extract_device*)dev)->out;
	fz_write_printf(ctx, out, "<clip_image_mask");
	fz_extract_matrix(ctx, out, ctm);
	fz_write_printf(ctx, out, " width=\"%d\" height=\"%d\"", image->w, image->h);
	fz_write_printf(ctx, out, "/>\n");*/
}

static void
fz_extract_pop_clip(fz_context *ctx, fz_device *dev)
{
	//fz_output *out = ((fz_extract_device*)dev)->out;
	//fz_write_printf(ctx, out, "<pop_clip/>\n");
}

static void
fz_extract_begin_mask(fz_context *ctx, fz_device *dev, const fz_rect *bbox, int luminosity, fz_colorspace *colorspace, const float *color, const fz_color_params *color_params)
{
	//fz_output *out = ((fz_extract_device*)dev)->out;
	//fz_write_printf(ctx, out, "<mask bbox=\"%g %g %g %g\" s=\"%s\"",
	//	bbox->x0, bbox->y0, bbox->x1, bbox->y1,
	//	luminosity ? "luminosity" : "alpha");
	//fz_write_printf(ctx, out, ">\n");
}

static void
fz_extract_end_mask(fz_context *ctx, fz_device *dev)
{
	//fz_output *out = ((fz_extract_device*)dev)->out;
	//fz_write_printf(ctx, out, "</mask>\n");
}

static void
fz_extract_begin_group(fz_context *ctx, fz_device *dev, const fz_rect *bbox, fz_colorspace *cs, int isolated, int knockout, int blendmode, float alpha)
{
	//fz_output *out = ((fz_extract_device*)dev)->out;
	//fz_write_printf(ctx, out, "<group bbox=\"%g %g %g %g\" isolated=\"%d\" knockout=\"%d\" blendmode=\"%s\" alpha=\"%g\">\n",
	//	bbox->x0, bbox->y0, bbox->x1, bbox->y1,
	//	isolated, knockout, fz_blendmode_name(blendmode), alpha);
}

static void
fz_extract_end_group(fz_context *ctx, fz_device *dev)
{
	//fz_output *out = ((fz_extract_device*)dev)->out;
	//fz_write_printf(ctx, out, "</group>\n");
}

static int
fz_extract_begin_tile(fz_context *ctx, fz_device *dev, const fz_rect *area, const fz_rect *view, float xstep, float ystep, const fz_matrix *ctm, int id)
{
	//fz_output *out = ((fz_extract_device*)dev)->out;
	//fz_write_printf(ctx, out, "<tile id=\"%d\"", id);
	//fz_write_printf(ctx, out, " area=\"%g %g %g %g\"", area->x0, area->y0, area->x1, area->y1);
	//fz_write_printf(ctx, out, " view=\"%g %g %g %g\"", view->x0, view->y0, view->x1, view->y1);
	//fz_write_printf(ctx, out, " xstep=\"%g\" ystep=\"%g\"", xstep, ystep);
	//fz_extract_matrix(ctx, out, ctm);
	//fz_write_printf(ctx, out, ">\n");
	return 0;
}

static void
fz_extract_end_tile(fz_context *ctx, fz_device *dev)
{
	//fz_output *out = ((fz_extract_device*)dev)->out;
	//fz_write_printf(ctx, out, "</tile>\n");
}

static void
fz_extract_begin_layer(fz_context *ctx, fz_device *dev, const char *name)
{
	//fz_output *out = ((fz_extract_device*)dev)->out;
	//fz_write_printf(ctx, out, "<layer name=\"%s\">\n", name);
}

static void
fz_extract_end_layer(fz_context *ctx, fz_device *dev)
{
	//fz_output *out = ((fz_extract_device*)dev)->out;
	//fz_write_printf(ctx, out, "</layer>\n");
}

fz_device *fz_new_extract_device(fz_context *ctx, int pagenum, fz_output *out)
{
	fz_extract_device *dev = fz_new_derived_device(ctx, fz_extract_device);

	//dev->super.fill_path = fz_extract_fill_path;
	//dev->super.stroke_path = fz_extract_stroke_path;
	//dev->super.clip_path = fz_extract_clip_path;
	//dev->super.clip_stroke_path = fz_extract_clip_stroke_path;

	//dev->super.fill_text = fz_extract_fill_text;
	//dev->super.stroke_text = fz_extract_stroke_text;
	//dev->super.clip_text = fz_extract_clip_text;
	//dev->super.clip_stroke_text = fz_extract_clip_stroke_text;
	//dev->super.ignore_text = fz_extract_ignore_text;

	dev->super.fill_shade = fz_extract_fill_shade;
	dev->super.fill_image = fz_extract_fill_image;
	dev->super.fill_image_mask = fz_extract_fill_image_mask;
	dev->super.clip_image_mask = fz_extract_clip_image_mask;

	//dev->super.pop_clip = fz_extract_pop_clip;

	//dev->super.begin_mask = fz_extract_begin_mask;
	//dev->super.end_mask = fz_extract_end_mask;
	//dev->super.begin_group = fz_extract_begin_group;
	//dev->super.end_group = fz_extract_end_group;

	//dev->super.begin_tile = fz_extract_begin_tile;
	//dev->super.end_tile = fz_extract_end_tile;

	//dev->super.begin_layer = fz_extract_begin_layer;
	//dev->super.end_layer = fz_extract_end_layer;

	dev->out = out;
	dev->pagenum = pagenum;

	return (fz_device*)dev;
}
