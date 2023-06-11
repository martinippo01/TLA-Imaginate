from PIL import Image, ImageEnhance
import random

def overlay_images(background_image, overlay_image, position):
	modified_image = background_image.copy()
	overlay_with_alpha = Image.new("RGBA", overlay_image.size)
	overlay_with_alpha = Image.blend(overlay_with_alpha, overlay_image, 1)
	modified_image.paste(overlay_with_alpha, position, overlay_with_alpha)
	return modified_image
file_paths = [, ]
images_map = lambda image: Image.open(image).convert("RGBA")
images = list(map(images_map, file_paths))




# SAVE_IMAGES 
count = 0
for image in images:
	image.save("exported-" + str(count) + ".png")
	count = count + 1

