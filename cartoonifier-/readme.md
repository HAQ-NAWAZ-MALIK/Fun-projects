
# Cartoonifier Python Project


![sam](https://github.com/HAQ-NAWAZ-MALIK/Fun-projects/assets/86514900/aeb6af0f-37fa-4513-98b2-ada002195a98)


![SAMPLE COOTNISH](https://github.com/HAQ-NAWAZ-MALIK/Fun-projects/assets/86514900/618cd500-e1ed-4879-b74c-ed35a04f7bb2)


This Python project allows you to convert your images into cartoon-like images using OpenCV and other image processing libraries.

## Prerequisites
---
- Python 3.x
- OpenCV
- EasyGUI
- NumPy
- ImageIO
- Matplotlib
- Tkinter
- Pillow
---
## Installation

1. Clone the repository or download the source code.
2. Install the required dependencies using pip:

```
pip install opencv-python easygui numpy imageio matplotlib pillow
```

## Usage

1. Run the `cartoonifier-python-project.py` script.
2. A GUI window will open.
3. Click the "Cartoonify an Image" button to select an image file from your system.
4. After selecting the image, the cartoonification process will start, and the original image, along with the intermediate steps, will be displayed.
5. Once the process is complete, a "Save cartoon image" button will appear. Click it to save the cartoonified image to the same directory as the original image.

## How it Works

The cartoonification process involves the following steps:

1. Load the original image using OpenCV.
2. Convert the image to grayscale.
3. Apply median blur to smooth the grayscale image.
4. Retrieve the edges using adaptive thresholding.
5. Apply bilateral filter to remove noise while preserving edges.
6. Mask the color image with the edge image to create the cartoon effect.
7. Display the original image and the intermediate steps using Matplotlib.
8. Save the cartoonified image to the specified location.

## Contributing

Contributions are welcome! If you find any issues or have suggestions for improvements, please create a new issue or submit a pull request.

## License

This project is licensed under the [MIT License](LICENSE).

## Acknowledgments

This project was inspired by various online tutorials and examples on image processing with OpenCV and Python.
```
