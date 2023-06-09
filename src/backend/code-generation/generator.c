#include "../support/logger.h"
#include "generator.h"

#include <stdio.h>

static FILE * fd_py;
int isRenderAll;

/**
 * Implementación de "generator.h".
 */

void Generator(ProgramNode * program) {
	// Creamos el archivo output
	fd_py = fopen("generator.py", "w");

	// Importamos el paquete
	fprintf(fd_py, "from PIL import Image, ImageEnhance\n");


	LogDebug("Llegue al program Node .");
	generateImagenate(program->imaginate);

	LogDebug("Generando archivo .py");


	fclose(fd_py);

	int errorCode = system("python3 generator.py");

	printf("\n\n\n Erro code = %d\n", errorCode);

}

void generateImagenate(ImaginateNode * imaginateNode){
	LogDebug("Llegue al imaginate Node .");

	// Is the render a normal render or a renderAll
	isRenderAll = imaginateNode->render->type == RENDERALL__;

	generateFocus(imaginateNode->focus);

	generateForEachFocus(imaginateNode->focuses);
	
	generateMethodChain(imaginateNode->methodChain);
	
	generateRender(imaginateNode->render);
}

void generateParam(ParamNode * paramNode){
	LogDebug("Llegue al param Node .");
	generateValue(paramNode->value);
}

void generateForEachFocus(ForEachFocusNode * forEachFocusNode){
	LogDebug("Llegue al forEachFocus Node .");

	if(forEachFocusNode == NULL)
		return;
	fprintf(fd_py, "file_paths = [");
	generateParamsBlock(forEachFocusNode->var);
	fprintf(fd_py, "]\n");
	fprintf(fd_py, "images_map = lambda image: Image.open(image)\n");
	fprintf(fd_py, "images = list(map(images_map, file_paths))\n");

}


// from PIL import Image, ImageEnhance

// # Define the file paths of the images
// file_paths = ["path/to/image1.jpg", "path/to/image2.jpg", "path/to/image3.jpg"]

// # Define the desired contrast enhancement factor
// contrast_factor = 2.0

// # Define a lambda function to apply the filters to each image
// apply_filters = lambda file_path: ImageEnhance.Contrast(Image.open(file_path)).enhance(contrast_factor)

// # Apply the filters to each image using the map() function
// modified_images = map(apply_filters, file_paths)

// # Save the modified images back to the original file paths
// for modified_image, file_path in zip(modified_images, file_paths):
//     modified_image.save(file_path)



void generateParams(ParamsNode * paramsNode){
	LogDebug("Llegue al params Node .");
	
		
	generateParam(paramsNode->param);	

	if(paramsNode->next != NULL){
		fprintf(fd_py, ", ");
		generateParams(paramsNode->next);
	}
}


void generateParamsBlock(ParamsBlockNode * paramsBlockNode){
	LogDebug("Llegue al paramsBlock Node .");
	generateParams(paramsBlockNode->params);
}



void generateFocus(FocusNode * focusNode){
	LogDebug("Llegue al focus Node .");
	if(focusNode == NULL)
		return;

	fprintf(fd_py, "file_paths = [");
	generateParamsBlock(focusNode->var);
	fprintf(fd_py, "]\n");
	fprintf(fd_py, "images = [Image.open(name)) for name in file_paths]\n");
	/*fprintf(fd_py, "images_map = lambda image: Image.open(image)\n");
	fprintf(fd_py, "images = list(map(images_map, file_paths))\n");*/

}



void generateMethodChain(MethodChainNode * methodChainNode){
	LogDebug("Llegue al methodChain Node .");
	
	generateMethod(methodChainNode->method);
	
	if(methodChainNode->next != NULL)
		generateMethodChain(methodChainNode->next);
}


void generateMethod(MethodNode * methodNode){
	LogDebug("Llegue al method Node .");
	//TODO Fijate que methodNode->params es un arreglo de ValueNode.
	
	//TODO Fijate que methodNode->identifier es un arreglo tiene internamente un string
	if(methodNode == NULL)
		return;
	
	switch (methodNode->identifier->type)
	{
	case CUSTOM_METHOD:
		LogDebug("Llegue a un method CUSTOM");
		break;
	
	case ADDBLACKANDWHITE_METHOD:
		LogDebug("Llegue a un method ADDBLACKANDWHITE");
		break;

	case ADDCONTRAST_METHOD:
		LogDebug("Llegue a un method ADDCONTRAST");
		
		//fprintf(fd_py, "image = ImageEnhance.Contrast(image).enhance(");
		/*
		fprintf(fd_py, "apply_filters = lambda image: ImageEnhance.Contrast(image).enhance(");
		generateParamsBlock(methodNode->params);
		fprintf(fd_py, ")\n");
		fprintf(fd_py, "modified_images = list(map(apply_filters, images))\n");
		*/
		fprintf(fd_py, "images = [ ImageEnhance.Contrast(image).enhance(");
		generateParamsBlock(methodNode->params);
		fprintf(fd_py, ") for image in images]\n");
		break;

	case ADDGRAYSCALE_METHOD:
		LogDebug("Llegue a un method ADDGRAYSCALE");
		break;

	case ADDBACKGROUND_METHOD:
		LogDebug("Llegue a un method ADDBACKGROUND");
		break;

	case ADDFLAVOUR_METHOD:
		LogDebug("Llegue a un method ADDFLAVOUR");
		break;

	case PICKFLAVOUR_METHOD:
		LogDebug("Llegue a un method PICKFLAVOUR");
		break;

	default:
		LogDebug("Llegue a un method NO CONOCIDO");
		break;
	}


	

	LogDebug("Llegue a un method custom");


	
}


void generateValue(ValueNode * valueNode){
	LogDebug("Llegue al value Node .");
	switch (valueNode->type)
	{
	case INT_VALUE:

		LogDebug("Llegue al value Node con INT.");
		fprintf(fd_py, "%d", valueNode->value.intValue);
		break;
	case STRING_VALUE:
		LogDebug("Llegue al value Node con STRING.");
		fprintf(fd_py, "%s", valueNode->value.stringValue);
		break;
	case OBJECT_VALUE:
		LogDebug("Llegue al value Node con OBJECT.");
		break;
	default:
		break;
	}
}
void generateRender(RenderNode * renderNode){
	LogDebug("Llegue al render Node .");
	switch (renderNode->type)
	{
	case RENDER__:
		//for modified_image, file_path in zip(modified_images, file_paths):
//     modified_image.save(file_path)
		LogDebug("Llegue al render Node con RENDER__.");
		fprintf(fd_py, "count = 0\nfor image, file_path in zip(images, file_paths):\n\timage.save(\"exported-\" + str(count) + \".png\")\n\tcount = count + 1");
		break;
	case RENDERALL__:
		LogDebug("Llegue al render Node con RENDERALL__.");
		break;
	default:
		break;
	}
}