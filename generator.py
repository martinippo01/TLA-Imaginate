from PIL import Image, ImageEnhance
file_paths = ["src/backend/code-generation/python/focus/Water.png", "src/backend/code-generation/python/focus/Fire.png", "src/backend/code-generation/python/focus/Plants.png"]
images_map = lambda image: Image.open(image)
images = list(map(images_map, file_paths))
images = [ ImageEnhance.Contrast(image).enhance(0) for image in images]
count = 0
for image, file_path in zip(images, file_paths):
	image.save("exported-" + str(count) + ".png")
	count = count + 1
