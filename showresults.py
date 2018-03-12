import dnest4.classic as dn4
import matplotlib.pyplot as plt

dn4.postprocess()

# Load the data and posterior samples
data = dn4.my_loadtxt("data/example_data.txt").reshape((75, 80, 100))
posterior_sample = dn4.my_loadtxt("posterior_sample.txt")
indices = dn4.load_column_names("sample.txt")["indices"]

# Residual of first posterior sample (summed over frequency dimension)
image_start = indices["model_image[0][0][0]"]
model = posterior_sample[0, image_start:].reshape((75, 80, 100))
plt.imshow(data.sum(axis=2) - model.sum(axis=2), cmap="coolwarm")
plt.title("Residuals")
plt.show()

