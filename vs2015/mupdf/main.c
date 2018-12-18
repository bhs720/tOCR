#include <stdio.h>

#include "mupdf\fitz.h"
#include "mupdf\fitz\image.h"
#include "extract-device.h"
#include "info-device.h"

void run_pdf_info(fz_context *ctx, fz_document *doc, int pagecount)
{
	fz_page *page = NULL;
	fz_device *dev = NULL;

	for (int i = 0; i < pagecount; i++)
	{
		page = fz_load_page(ctx, doc, i);
		dev = fz_new_info_device(ctx, i, fz_stdout(ctx));

		fz_enable_device_hints(ctx, dev, FZ_DONT_INTERPOLATE_IMAGES);
		fz_enable_device_hints(ctx, dev, FZ_NO_CACHE);

		fz_run_page_contents(ctx, page, dev, &fz_identity, NULL);
		fz_close_device(ctx, dev);
		fz_drop_device(ctx, dev);

		fz_drop_page(ctx, page);

		dev = NULL;
		page = NULL;
	}
}

void run_pdf_extraction(fz_context *ctx, fz_document *doc, int pagecount, char *output_base)
{

}

int main(int argc, char **argv)
{
	fz_context *ctx = NULL;
	fz_document *doc = NULL;
	char *input_file = NULL;
	char *output_base = NULL;
	int pagecount = 0;

	if (argc < 2)
	{
		fprintf(stderr, "Missing filename argument\r\n");
		return -1;
	}
	else
	{
		input_file = argv[1];
	}

	if (argc == 3)
	{
		output_base = argv[2];
	}

	ctx = fz_new_context(NULL, NULL, FZ_STORE_DEFAULT);
	if (!ctx)
	{
		fprintf(stderr, "Failed to create mupdf context\r\n");
		return -1;
	}

	fz_try(ctx)
	{
		fz_register_document_handlers(ctx);
	}
	fz_catch(ctx)
	{
		fprintf(stderr, "Failed to register document handlers\r\n");
		fz_drop_context(ctx);
		return -1;
	}

	fz_try(ctx)
	{
		doc = fz_open_document(ctx, input_file);
		pagecount = fz_count_pages(ctx, doc);
		fprintf(stdout, "pagecount=%d\r\n", pagecount);
		
		if (output_base == NULL)
		{
			run_pdf_info(ctx, doc, pagecount);
		}
		else
		{
			run_pdf_extraction(ctx, doc, pagecount, output_base);
		}

		fz_drop_document(ctx, doc);
	}
	fz_catch(ctx)
	{
		fprintf(stderr, "Failed to open document: %s\r\n", input_file);
		return -1;
	}

	if (ctx)
	{
		fz_drop_context(ctx);
	}

	fprintf(stdout, "Program finished\r\n");
	getc(stdin);
	return 0;
}