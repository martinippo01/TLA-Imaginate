from PIL import Image, ImageEnhance
import random

def overlay_images(background_image, overlay_image, position):
	modified_image = background_image.copy()
	overlay_with_alpha = Image.new("RGBA", overlay_image.size)
	overlay_with_alpha = Image.blend(overlay_with_alpha, overlay_image, 1)
	modified_image.paste(overlay_with_alpha, position, overlay_with_alpha)
	return modified_image
file_paths = [, , ]
images_map = lambda image: Image.open(image).convert("RGBA")
images = list(map(images_map, file_paths))


# ADD_BACKGROUND 
background_image = Image.open().convert("RGBA")
position = (0, 0)
images = [ overlay_images(background_image, image, position) for image in images]


# ADD_FLAVOUR 
flavour_image = Image.open().convert("RGBA")
position = (0, 0)
images = [ overlay_images(image, flavour_image, position) for image in images]


# PICK_FLAVOUR 
possible_flavours = [, , ]
i=0
new_image_list = []
for image in images:
	for flavour in possible_flavours:
		new_image_list.append(overlay_images(image, Image.open(flavour), position))
		i+=1
images = [new_image_list[i] for i in range(len(new_image_list))]


# ADD_FLAVOUR 
flavour_image = Image.open().convert("RGBA")
position = (0, 0)
images = [ overlay_images(image, flavour_image, position) for image in images]




# SAVE_IMAGES 
count = 0
for image in images:
	image.save("exported-" + str(count) + ".png")
	count = count + 1

