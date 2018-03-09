"""
Generate and save an example dataset in plain text format.
"""

# Imports
import matplotlib.pyplot as plt
from numba import jit
import numpy as np
import numpy.random as rng
import os

# Set RNG seed
rng.seed(0)

# Number of pixels in each dimension - x, y, frequency.
num_pixels = {"x": 75, "y": 80, "f": 100}

# Pixel widths (whatever units)
dx, dy, df = 0.1, 0.1, 1.0
assert(dx == dy)

# Image limits (these apply to pixel edges, not centers)
x_min, x_max = 0.0, num_pixels["x"]*dx
y_min, y_max = 0.0, num_pixels["y"]*dy
f_min, f_max = 0.0, num_pixels["f"]*df

# Coordinates of pixel centers
xs = np.linspace(x_min + 0.5*dx, x_max - 0.5*dx, num_pixels["x"])
ys = np.linspace(y_min + 0.5*dy, y_max - 0.5*dy, num_pixels["y"])
fs = np.linspace(f_min + 0.5*df, f_max - 0.5*df, num_pixels["f"])

# Source properties
num_sources = 10

# Central positions - note restricted domain.
# In the inference this will be widened.
x_sources = x_min + (x_max - x_min)*rng.rand(num_sources)
y_sources = y_min + (y_max - y_min)*rng.rand(num_sources)
f_sources = f_min + (f_max - f_min)*rng.rand(num_sources)

# mass, axis ratio, orientation angle
m_sources = np.exp(0.3*rng.randn(num_sources))
q_sources = np.exp(0.3*rng.randn(num_sources))
theta_sources = np.pi*rng.rand(num_sources)
width_sources = np.exp(0.3*rng.randn(num_sources))
fwidth_sources = 40.0*np.exp(0.3*rng.randn(num_sources))

@jit
def surface_brightness(x, y, f):
    """
    Compute the total surface brightness of all the sources
    at a given position and frequency.
    """
    result = 0.0
    for i in range(num_sources):
        coeff = m_sources[i]/(2.0*np.pi*width_sources[i]**2)
        cos_theta = np.cos(theta_sources[i])
        sin_theta = np.sin(theta_sources[i])
        xx =  cos_theta*(x - x_sources[i]) + sin_theta*(y - y_sources[i])
        yy = -sin_theta*(x - x_sources[i]) + cos_theta*(y - y_sources[i])
        rsq = q_sources[i]*xx**2 + yy**2/q_sources[i]
        f_gaussian = np.exp(-0.5*((f - f_sources[i])/fwidth_sources[i])**2)\
                            /np.sqrt(2*np.pi)/fwidth_sources[i]
        result += coeff*np.exp(-0.5*rsq)*f_gaussian
    return result


@jit
def compute_images():
    """
    Produce the 3D array of surface brightnesses.
    """
    images = np.empty((num_pixels["x"], num_pixels["y"], num_pixels["f"]))
    for i in range(images.shape[0]):
        for j in range(images.shape[1]):
            for k in range(images.shape[2]):
                images[i, j, k] = surface_brightness(xs[i], ys[j], fs[k])
    return images

# Compute and plot images
images = compute_images()

# Add noise
images += 0.001*rng.randn(images.shape[0], images.shape[1], images.shape[2])

# Save data
outfile = open("../data/example_data.txt", "w")
for i in range(images.shape[0]):
    for j in range(images.shape[1]):
        for k in range(images.shape[2]):
            outfile.write(str(images[i, j, k]) + "\n")
outfile.close()

for i in range(images.shape[2]):
    plt.clf()
    plt.imshow(images[:,:,i])
    plt.title("Frequency {k}/{N}".format(k=i+1, N=images.shape[2]))
    filename = "images/" + "%0.6d"%(i+1) + ".png"
    plt.savefig(filename)
    print(filename)

# Make movie
os.system("ffmpeg -r 15 -i images/%06d.png " + \
          "-c:v h264 -b:v 4192k images/movie.mkv")

