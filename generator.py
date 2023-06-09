from PIL import Image, ImageEnhance
file_paths = []
images = [Image.open(name)) for name in file_paths]
count = 0
for image, file_path in zip(images, file_paths):
	image.save("exported-" + str(count) + ".png")
	count = count + 1