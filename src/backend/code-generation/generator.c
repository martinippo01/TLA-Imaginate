#include "../support/logger.h"
#include "generator.h"

#include <stdio.h>

static FILE * fd_py;
int isRenderAll;


void pickFlavourAll(MethodNode* methodNode, char* identation);
void pickFlavourSimple(MethodNode* methodNode, char* identation);
/**
 * Implementación de "generator.h".
 */

void Generator(ProgramNode * program, int execute, char *outputFileName) {
	// Creamos el archivo output
	fd_py = fopen(outputFileName, "w");

	// Importamos el paquete
	fprintf(fd_py, "from PIL import Image, ImageEnhance\n");
	fprintf(fd_py, "import random\n\n");

	fprintf(fd_py, "def overlay_images(background_image, overlay_image, position):\n");
	fprintf(fd_py, "\tmodified_image = background_image.copy()\n");
	fprintf(fd_py, "\toverlay_with_alpha = Image.new(\"RGBA\", overlay_image.size)\n");
	fprintf(fd_py, "\toverlay_with_alpha = Image.blend(overlay_with_alpha, overlay_image, 1)\n");
	fprintf(fd_py, "\tmodified_image.paste(overlay_with_alpha, position, overlay_with_alpha)\n");	

	fprintf(fd_py, "\treturn modified_image\n");

	LogDebug("Llegue al program Node .");
	generateImagenate(program->imaginate);
	fprintf(fd_py, "\n"); // Some IDEs recommned having a emty last line


	LogDebug("Generando archivo .py");


	fclose(fd_py);

	if(execute)
		system("python3 generator.py");

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
	fprintf(fd_py, "images_map = lambda image: Image.open(image).convert(\"RGBA\")\n");
	fprintf(fd_py, "images = list(map(images_map, file_paths))\n");

}

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
	fprintf(fd_py, "images = [Image.open(name).convert(\"RGBA\") for name in file_paths]\n");
	/*fprintf(fd_py, "images_map = lambda image: Image.open(image)\n");
	fprintf(fd_py, "images = list(map(images_map, file_paths))\n");*/

}



void generateMethodChain(MethodChainNode * methodChainNode){	LogDebug("Llegue al methodChain Node .");
	
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
	
	fprintf(fd_py, "\n\n");

	char* identation = "";
	if(!isRenderAll && methodNode->optional->isQuestionMarkPresent){
		fprintf(fd_py, "# Optional\n");
		fprintf(fd_py, "if random.randint(0, 1) == 1:\n");
		identation = "\t";
	}


	switch (methodNode->identifier->type)
	{
	case CUSTOM_METHOD:
		LogDebug("Llegue a un method CUSTOM");
		// TODO
		break;
	
	case ADDBLACKANDWHITE_METHOD:
		LogDebug("Llegue a un method ADDBLACKANDWHITE");
		fprintf(fd_py, "%s# BLACK_AND_WHITE \n", identation);

		fprintf(fd_py, "%simages = [ image.convert(\'L\').convert(\"RGBA\") for image in images]\n", identation);
		break;

	case ADDCONTRAST_METHOD:
		LogDebug("Llegue a un method ADDCONTRAST");
		fprintf(fd_py, "%s# ADD_CONTRAST \n", identation);

		fprintf(fd_py, "%simages = [ ImageEnhance.Contrast(image).enhance(", identation);
		generateParamsBlock(methodNode->params);
		fprintf(fd_py, ") for image in images]\n");
		break;

	case ADDGRAYSCALE_METHOD:
		LogDebug("Llegue a un method ADDGRAYSCALE");
		fprintf(fd_py, "%s# ADD_GRAY_SCALE \n", identation);

		fprintf(fd_py, "%simages = [ ImageEnhance.Contrast(image.convert(\'L\')).enhance(1.5).convert(\"RGBA\") for image in images]\n", identation);

		break;

	case ADDBACKGROUND_METHOD:
		LogDebug("Llegue a un method ADDBACKGROUND");
		fprintf(fd_py, "%s# ADD_BACKGROUND \n", identation);

		fprintf(fd_py, "%sbackground_image = Image.open(", identation);
		generateParamsBlock(methodNode->params);
		fprintf(fd_py, ").convert(\"RGBA\")\n");

		fprintf(fd_py, "%sposition = (0, 0)\n", identation);
		
		fprintf(fd_py, "%simages = [ overlay_images(background_image, image, position) for image in images]\n", identation);

		break;

	case ADDFLAVOUR_METHOD:
		LogDebug("Llegue a un method ADDFLAVOUR");
		fprintf(fd_py, "%s# ADD_FLAVOUR \n", identation);
		
		fprintf(fd_py, "%sflavour_image = Image.open(", identation);
		generateParamsBlock(methodNode->params);
		fprintf(fd_py, ").convert(\"RGBA\")\n");

		fprintf(fd_py, "%sposition = (0, 0)\n", identation);
		fprintf(fd_py, "%simages = [ overlay_images(image, flavour_image, position) for image in images]\n", identation);

		break;

	case PICKFLAVOUR_METHOD:
		LogDebug("Llegue a un method PICKFLAVOUR");
		fprintf(fd_py, "%s# PICK_FLAVOUR \n", identation);

		if(isRenderAll)
			pickFlavourAll(methodNode, identation);
		else
			pickFlavourSimple(methodNode, identation);
		
		break;

	default:
		LogDebug("Llegue a un method NO CONOCIDO");
		break;
	}

	
}

void pickFlavourAll(MethodNode* methodNode, char* identation){

	fprintf(fd_py, "%spossible_flavours = [", identation);
	generateParamsBlock(methodNode->params);
	fprintf(fd_py, "]\n");

	fprintf(fd_py, "%si=0\n", identation);

	fprintf(fd_py, "%snew_image_list = []\n", identation);

	fprintf(fd_py, "%sfor image in images:\n", identation);

	fprintf(fd_py, "%s\tfor flavour in possible_flavours:\n", identation);

	fprintf(fd_py, "%s\t\tnew_image_list.append(overlay_images(image, Image.open(flavour), position))\n", identation);

	fprintf(fd_py, "%s\t\ti+=1\n", identation);

	fprintf(fd_py, "%simages = [new_image_list[i] for i in range(len(new_image_list))]\n", identation);

}


void pickFlavourSimple(MethodNode* methodNode, char* identation){
	fprintf(fd_py, "%spossible_flavours = [", identation);
	generateParamsBlock(methodNode->params);
	fprintf(fd_py, "]\n");

	fprintf(fd_py, "%sflavour_image = Image.open(possible_flavours[random.randint(0, len(possible_flavours) - 1)]).convert(\"RGBA\")\n", identation);
	

	fprintf(fd_py, "%sposition = (0, 0)\n", identation);
	fprintf(fd_py, "%simages = [ overlay_images(image, flavour_image, position) for image in images]\n", identation);
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
	fprintf(fd_py, "\n\n");

	switch (renderNode->type)
	{
	case RENDER__:

		LogDebug("Llegue al render Node con RENDER__.");
		fprintf(fd_py, "# SAVE_IMAGES \n");

		fprintf(fd_py, "count = 0\n");
		fprintf(fd_py, "for image, file_path in zip(images, file_paths):\n");
		fprintf(fd_py, "\timage.save(\"exported-\" + str(count) + \".png\")\n");
		fprintf(fd_py, "\tcount = count + 1\n");
		break;
	case RENDERALL__:
		LogDebug("Llegue al render Node con RENDERALL__.");
		fprintf(fd_py, "# SAVE_IMAGES \n");

		fprintf(fd_py, "count = 0\n");
		fprintf(fd_py, "for image in images:\n");
		fprintf(fd_py, "\timage.save(\"exported-\" + str(count) + \".png\")\n");
		fprintf(fd_py, "\tcount = count + 1\n");
		break;
	default:
		break;
	}
}