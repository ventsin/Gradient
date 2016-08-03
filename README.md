# Gradient
GUI for generating random (mostly) gradients.
Can output to the following formats: JPG, PNG, TGA, DDS, BMP and PSD.

Uses Nana C++ for interface and SFML for gradient interpolation and rendering preview.

The project itself is more a proof-of-concept of integration between the libraries than a fully-capable software solution.


# Instructions
Hit 'Generate' to randomize the gradient.

'Manual' can be used to set the current gradient colors manually and/or the final image resolution.

'Preview' will open/close the preview window.

'Save' will write the gradient to disk with the selected name and format.
The image will still be written if there is nothing typed in the textbox.
If there is no extension in the typed file name, or if the extension does not match ".jpg", ".png", ".tga", ".dds", ".bmp" or ".psd", the file will be written in the JPEG format (choosen for smaller final size).

# License
The code is distributed under the GNU General Public License (GNU GPLv3) on the basis that this project can be used freely by anyone for whatever purpose they see fit, it can be modified and shared. Not that it is a really relevant piece of code anyway.

As mentioned, the project is more about the integration of the two libraries used in the program than about the gradient itself, so the relevant gradient-related code can be checked at the gradient-cmd repository (unavaliable as of now, will be up soon).
