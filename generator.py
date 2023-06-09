from PIL import Image, ImageEnhance
file_paths = [, , , , , ]
images_map = lambda image: Image.open(image)
images = list(map(images_map, file_paths))
images = [ ImageEnhance.Contrast(image).enhance(10, 20) for image in images]
