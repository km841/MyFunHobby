from PIL import Image
import os


folder_path = input(r"folder address : ")
if not (os.path.exists(folder_path)):
    print("Not found address..")
    exit()

if (os.path.isfile(folder_path)):
    print("This is file..")
    exit()

anim_filename = input(r"anim_filename : ")
if (os.path.isdir(anim_filename)):
    print("This is folder..")
    exit()

sprite_offset = int(input(r"offset : "))

anim_filename = anim_filename + ".anim"

new_folder_path = os.path.join(folder_path, "Revision")
if not (os.path.exists(new_folder_path)):
    os.mkdir(new_folder_path)

max_width = -1
max_height = -1

for filename in os.listdir(folder_path):
    if filename.endswith(".png"):
        img_path = os.path.join(folder_path, filename)
        with Image.open(img_path) as img:
            width, height = img.size
            if (width > max_width):
                max_width = width
            if (height > max_height):
                max_height = height


print(f"max_width : {max_width} , max_height : {max_height}")
new_size = (max_width, max_height)
file_count = 0
for filename in os.listdir(folder_path):
    if filename.endswith(".png"):
        img_path = os.path.join(folder_path, filename)
        with Image.open(img_path) as img:
            new_img = Image.new('RGBA', new_size, (255, 255, 255, 0))
            new_img.paste(img, ((new_size[0]-img.size[0])//2, (new_size[1]-img.size[1])//2))

            new_filename = os.path.join(new_folder_path, "new_" + filename)
            new_img.save(new_filename)
            file_count += 1

#

acc_width = 0
anim_abspath = os.path.join(new_folder_path, anim_filename)
with open(anim_abspath, "w") as f:
    f.write(str(file_count))
    f.write('\n')
    f.write(anim_filename)
    f.write('\n')
    f.write('\n')
    for i in range(file_count):
        acc_width += sprite_offset
        f.write(str(acc_width) + " " + "0\n") #Left Top
        
        acc_width += max_width - sprite_offset
        
        f.write(str(max_width - (sprite_offset * 2)) + " " + str(max_height) + "\n") #Size
        f.write("0 0\n") #offset
        f.write("1\n")   #duration


def sort_func(filename):
    if len(filename.split('.')[0]) >= 2:
        if '_' in filename.split('.')[0]:
            filename_num = filename.split('.')[0].split('_')[-1]
        else:
            filename_num = filename.split('.')[0][-2:]
        return int(filename_num)
    elif len(filename.split('.')[0]) == 1:
        return int(filename.split('.')[0][-1:])
    else:
        return 0

png_file_list = []
for filename in os.listdir(new_folder_path):
    if filename.endswith(".png"):
        png_file_list.append(filename)

png_file_list = sorted(png_file_list, key=sort_func)

img_list = []
for filename in png_file_list:
    if filename.endswith(".png"):
        img_abspath = os.path.join(new_folder_path, filename)
        img = Image.open(img_abspath)
        img_list.append(img)
        print(filename)

widths, heights = zip(*(i.size for i in img_list))
total_width = sum(widths)

new_img = Image.new('RGBA', (total_width, max_height), (255, 255, 255, 0))

x_offset = 0
for img in img_list:
    new_img.paste(img, (x_offset, 0))
    x_offset += img.size[0]

new_img.save(os.path.join(new_folder_path, 'merged_image.png'))
