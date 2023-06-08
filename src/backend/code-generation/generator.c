#include "../support/logger.h"
#include "generator.h"

#include <stdio.h>

/**
 * Implementación de "generator.h".
 */

void Generator(ProgramNode * program) {
	LogDebug("Llegue al program Node .");
	generateImagenate(program->imaginate);

	LogDebug("Generando archivo .py");

	FILE * fd_py = fopen("generator.py", "w");

	fprintf(fd_py, "from PIL import Image\noverlay_image = Image.open(\"src/backend/code-generation/python/focus/Water.png\").convert(\"RGBA\")\nbackground_image = Image.open(\"src/backend/code-generation/python/background/Bricks.png\").convert(\"RGBA\")\nbackground_image.paste(overlay_image, (0, 0), overlay_image)\nbackground_image.show()\nbackground_image.save(\"exported.png\")\n");

	fclose(fd_py);

	system("python3 generator.py");

}

void generateImagenate(ImaginateNode * imaginateNode){
	LogDebug("Llegue al imaginate Node .");
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
	//TODO Fijase que forEachFocusNode->var es un arreglo de ValueNode
	if(forEachFocusNode == NULL)
		return;
	generateParamsBlock(forEachFocusNode->var);
}

void generateParams(ParamsNode * paramsNode){
	LogDebug("Llegue al params Node .");
	generateParam(paramsNode->param);
	if(paramsNode->next != NULL)
		generateParams(paramsNode->next);
}
void generateParamsBlock(ParamsBlockNode * paramsBlockNode){
	LogDebug("Llegue al paramsBlock Node .");
	generateParams(paramsBlockNode->params);
}
void generateFocus(FocusNode * focusNode){
	LogDebug("Llegue al focus Node .");
	if(focusNode == NULL)
		return;
	generateParamsBlock(focusNode->var);

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
	
	if(methodNode->identifier->type == OWN){
		LogDebug("Llegue a un method own");
		return;
	}
	LogDebug("Llegue a un method custom");

	
}
void generateValue(ValueNode * valueNode){
	LogDebug("Llegue al value Node .");
	switch (valueNode->type)
	{
	case INT_VALUE:
		LogDebug("Llegue al value Node con INT.");
		break;
	case STRING_VALUE:
		LogDebug("Llegue al value Node con STRING.");
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
		LogDebug("Llegue al render Node con RENDER__.");
		break;
	case RENDERALL__:
		LogDebug("Llegue al render Node con RENDERALL__.");
		break;
	default:
		break;
	}
}