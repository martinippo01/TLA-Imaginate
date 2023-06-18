#include "../support/logger.h"
#include "generator.h"

#include <stdio.h>

static FILE * fd_py;
int isRenderAll;


void pickFlavourAll(MethodNode* methodNode, char* identation, char* defIdentation);
void pickFlavourSimple(MethodNode* methodNode, char* identation, char* defIdentation);
/**
 * Implementación de "generator.h".
 */

void Generator(ProgramNode * program) {
	// Creamos el archivo output
	fd_py = fopen("generator.py", "w");

	// Importamos el paquete
	fprintf(fd_py, "from PIL import Image, ImageEnhance\n");
	fprintf(fd_py, "import random\n\n");

	fprintf(fd_py, "def overlay_images(background_image, overlay_image, position):\n");
	fprintf(fd_py, "\tmodified_image = background_image.copy()\n");
	fprintf(fd_py, "\toverlay_with_alpha = Image.new(\"RGBA\", overlay_image.size)\n");
	fprintf(fd_py, "\toverlay_with_alpha = Image.blend(overlay_with_alpha, overlay_image, 1)\n");
	fprintf(fd_py, "\tmodified_image.paste(overlay_with_alpha, position, overlay_with_alpha)\n");	

	fprintf(fd_py, "\treturn modified_image\n");

	fprintf(fd_py, "\n");
	//generateVariables(program->assignments);
	generateDefinitions(program->definitions);
	fprintf(fd_py, "\n");

	LogDebug("Llegue al program Node .");
	generateImagenate(program->imaginate);

	fprintf(fd_py, "\n"); // Some IDEs recommned having an emty last line


	LogDebug("Generando archivo .py");


	fclose(fd_py);

	int errorCode = system("python3 generator.py");


}


void generateDefinitions(DefinitionsNode * definitionsNode){
	
	LogDebug("Llegue a generateDefinitions");
	if(definitionsNode->definition == NULL)
		return;

	generateDefinition(definitionsNode->definition);

	generateDefinitions(definitionsNode->next);

}


void generateDefinition(DefinitionNode * definitionNode){
	LogDebug("Llegue a generateDefinition");

	fprintf(fd_py, "def %s(", definitionNode->identifier->name);
	generateArgumentsBlockNode(definitionNode->args);
	fprintf(fd_py, "):");
	generateMethodChain(definitionNode->methodChain, "\t");
	fprintf(fd_py, "\n");
	
}

void generateArgumentsBlockNode(ArgumentsBlockNode * argumentsBlockNode){
	LogDebug("Llegue a generateArgumentsBlockNode");
	
	ArgumentsNode * paramNode = argumentsBlockNode->params;
	fprintf(fd_py, "images");

	if(paramNode != NULL)
		fprintf(fd_py, ", ");

    while(paramNode != NULL && paramNode->arg != NULL) {
		generateArgumentsNode(paramNode);
		
		if(paramNode->next != NULL)
			fprintf(fd_py, ", ");
        paramNode = paramNode->next;
    }
}
void generateArgumentsNode(ArgumentsNode * argumentsNode){
	LogDebug("Llegue a generateArgumentsNode");

	fprintf(fd_py, "%s", argumentsNode->arg->value->value.stringValue);

}

	void generateVariables(AssignmentsNode * assignmentsNode){
		if(assignmentsNode->assignment == NULL)
			return;

		LogDebug("Llegue a assignmets");

		
		generateIdentifier(assignmentsNode->assignment->identifier);
		fprintf(fd_py, " = ");
		generateExpression(assignmentsNode->assignment->expression);
		fprintf(fd_py, "\n");
		
		generateVariables(assignmentsNode->next);
	}


	void generateIdentifier(IdentifierNode * identifierNode){
		
		LogDebug("Llegue a identifier");

		fprintf(fd_py, "%s", identifierNode->name);
	}


	void generateExpression(ValueNode * valueNode){
		
		LogDebug("Llegue a value");
		switch (valueNode->type)
		{
		case INT_VALUE:
			fprintf(fd_py, "%d", valueNode->value.intValue);
			break;
		
		case STRING_VALUE:
			fprintf(fd_py, "%s", valueNode->value.stringValue);
			break;

		case OBJECT_VALUE:
			//fprintf(fd_py, "%s", valueNode->value.objectValue->name);
			break;	

		default:
			break;
		}
		

	}

void generateImagenate(ImaginateNode * imaginateNode){
	LogDebug("Llegue al imaginate Node .");

	// Is the render a normal render or a renderAll
	isRenderAll = imaginateNode->render->type == RENDERALL__;

	generateFocus(imaginateNode->focus);

	generateForEachFocus(imaginateNode->focuses);
	
	generateMethodChain(imaginateNode->methodChain, "");
	
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





void generateMethodChain(MethodChainNode * methodChainNode, char * defIdentation){	
	
	LogDebug("Llegue al methodChain Node .");
	
	generateMethod(methodChainNode->method, defIdentation);
	
	if(methodChainNode->next != NULL)
		generateMethodChain(methodChainNode->next, defIdentation);
}


void generateMethod(MethodNode * methodNode, char * defIdentation){
	LogDebug("Llegue al method Node .");

	if(methodNode == NULL)
		return;
	
	fprintf(fd_py, "\n\n");

	char* identation = "";
	if(!isRenderAll && methodNode->optional->isQuestionMarkPresent){
		fprintf(fd_py, "%s# Optional\n", defIdentation);
		fprintf(fd_py, "%sif random.randint(0, 1) == 1:\n", defIdentation);
		identation = "\t";
	}


	switch (methodNode->identifier->type)
	{
	case CUSTOM_METHOD:
		LogDebug("Llegue al CUSTOM type");
		
		fprintf(fd_py, "%s%s%s(images", defIdentation, identation, methodNode->identifier->value.name);
		

		ParamsNode *params = methodNode->params->params;
		
		if(params != NULL && params->param != NULL)
			fprintf(fd_py, ", ");

		while(params != NULL && params->param != NULL){
			
			switch (params->param->value->type)
			{
			case STRING_VALUE:
				fprintf(fd_py, "%s", params->param->value->value.stringValue);
				break;
			case INT_VALUE:
				fprintf(fd_py, "%d", params->param->value->value.intValue);
				break;
			case OBJECT_VALUE:
				/* code */
				break;							
			default:
				break;
			}
			if(params->next != NULL)
				fprintf(fd_py, ", ");
			params = params->next;
		}
		fprintf(fd_py, ")\n");

		break;
	
	case ADDBLACKANDWHITE_METHOD:
		LogDebug("Llegue a un method ADDBLACKANDWHITE");
		fprintf(fd_py, "%s%s# BLACK_AND_WHITE \n", defIdentation, identation);

		fprintf(fd_py, "%s%simages = [ image.convert(\'L\').convert(\"RGBA\") for image in images]\n", defIdentation, identation);
		break;

	case ADDCONTRAST_METHOD:
		LogDebug("Llegue a un method ADDCONTRAST");
		fprintf(fd_py, "%s%s# ADD_CONTRAST \n", defIdentation, identation);

		fprintf(fd_py, "%s%simages = [ ImageEnhance.Contrast(image).enhance(", defIdentation, identation);
		generateParamsBlock(methodNode->params);
		fprintf(fd_py, ") for image in images]\n");
		break;

	case ADDGRAYSCALE_METHOD:
		LogDebug("Llegue a un method ADDGRAYSCALE");
		fprintf(fd_py, "%s%s# ADD_GRAY_SCALE \n", defIdentation, identation);

		fprintf(fd_py, "%s%simages = [ ImageEnhance.Contrast(image.convert(\'L\')).enhance(1.5).convert(\"RGBA\") for image in images]\n", defIdentation, identation);

		break;

	case ADDBACKGROUND_METHOD:
		LogDebug("Llegue a un method ADDBACKGROUND");
		fprintf(fd_py, "%s%s# ADD_BACKGROUND \n", defIdentation, identation);

		fprintf(fd_py, "%s%sbackground_image = Image.open(", defIdentation, identation);
		generateParamsBlock(methodNode->params);
		fprintf(fd_py, ").convert(\"RGBA\")\n");

		fprintf(fd_py, "%s%sposition = (0, 0)\n", defIdentation, identation);
		
		fprintf(fd_py, "%s%simages = [ overlay_images(background_image, image, position) for image in images]\n", defIdentation, identation);

		break;

	case ADDFLAVOUR_METHOD:
		LogDebug("Llegue a un method ADDFLAVOUR");
		fprintf(fd_py, "%s%s# ADD_FLAVOUR \n", defIdentation, identation);
		
		fprintf(fd_py, "%s%sflavour_image = Image.open(", defIdentation, identation);
		generateParamsBlock(methodNode->params);
		fprintf(fd_py, ").convert(\"RGBA\")\n");

		fprintf(fd_py, "%s%sposition = (0, 0)\n", defIdentation, identation);
		fprintf(fd_py, "%s%simages = [ overlay_images(image, flavour_image, position) for image in images]\n", defIdentation, identation);

		break;

	case PICKFLAVOUR_METHOD:
		LogDebug("Llegue a un method PICKFLAVOUR");
		fprintf(fd_py, "%s%s# PICK_FLAVOUR \n", defIdentation, identation);

		if(isRenderAll)
			pickFlavourAll(methodNode, identation, defIdentation);
		else
			pickFlavourSimple(methodNode, identation, defIdentation);
		
		break;

	default:
		LogDebug("Llegue a un method NO CONOCIDO");
		break;
	}

	
}

void pickFlavourAll(MethodNode* methodNode, char* identation, char *defIdentation){

	fprintf(fd_py, "%s%spossible_flavours = [", defIdentation, identation);
	generateParamsBlock(methodNode->params);
	fprintf(fd_py, "]\n");

	fprintf(fd_py, "%s%si=0\n", defIdentation, identation);

	fprintf(fd_py, "%s%snew_image_list = []\n", defIdentation, identation);

	fprintf(fd_py, "%s%sfor image in images:\n", defIdentation, identation);

	fprintf(fd_py, "%s%s\tfor flavour in possible_flavours:\n", defIdentation, identation);

	fprintf(fd_py, "%s%s\t\tnew_image_list.append(overlay_images(image, Image.open(flavour), position))\n", defIdentation, identation);

	fprintf(fd_py, "%s%s\t\ti+=1\n", defIdentation, identation);

	fprintf(fd_py, "%s%simages = [new_image_list[i] for i in range(len(new_image_list))]\n", defIdentation, identation);

}


void pickFlavourSimple(MethodNode* methodNode, char* identation, char * defIdentation){
	fprintf(fd_py, "%s%spossible_flavours = [", defIdentation, identation);
	generateParamsBlock(methodNode->params);
	fprintf(fd_py, "]\n");

	fprintf(fd_py, "%s%sflavour_image = Image.open(possible_flavours[random.randint(0, len(possible_flavours) - 1)]).convert(\"RGBA\")\n", defIdentation, identation);
	

	fprintf(fd_py, "%s%sposition = (0, 0)\n", defIdentation, identation);
	fprintf(fd_py, "%s%simages = [ overlay_images(image, flavour_image, position) for image in images]\n", defIdentation, identation);
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