from PIL import Image, ImageEnhance
import random

def overlay_images(background_image, overlay_image, position):
	modified_image = background_image.copy()
	overlay_with_alpha = Image.new("RGBA", overlay_image.size)
	overlay_with_alpha = Image.blend(overlay_with_alpha, overlay_image, 1)
	modified_image.paste(overlay_with_alpha, position, overlay_with_alpha)
	return modified_image

def applyGrayscaleAndContrast(images, value):

	# ADD_GRAY_SCALE 
	images = [ ImageEnhance.Contrast(image.convert('L')).enhance(1.5).convert("RGBA") for image in images]


file_paths = ["src/backend/code-generation/python/focos/luna.png"]
images = [Image.open(name).convert("RGBA") for name in file_paths]


applyGrayscaleAndContrast(images, 20)


# ADD_GRAY_SCALE 
images = [ ImageEnhance.Contrast(image.convert('L')).enhance(1.5).convert("RGBA") for image in images]


# SAVE_IMAGES 
count = 0
for image, file_path in zip(images, file_paths):
	image.save("exported-" + str(count) + ".png")
	count = count + 1

