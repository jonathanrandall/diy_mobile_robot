from PIL import Image
import os

# Define the directory containing the JPEG images
input_dir = '.'
output_dir = '.'

# Ensure output directory exists
os.makedirs(output_dir, exist_ok=True)

# Loop through all files in the input directory
for filename in os.listdir(input_dir):
    if filename.endswith('.jpg') or filename.endswith('.JPEG'):
        # Construct full file path
        file_path = os.path.join(input_dir, filename)

        # Open the image file
        with Image.open(file_path) as img:
            # Calculate the new size (50% of the original size)
            new_size = (int(img.width * 0.7), int(img.height * 0.7))

            # Resize the image to the new size
            scaled_img = img.resize(new_size, Image.Resampling.LANCZOS)

            # Save the scaled image to the output directory
            scaled_img.save(os.path.join(output_dir, filename))

            print(f"Scaled and saved {filename} to {output_dir}")

print("All images have been scaled by 50%!")
