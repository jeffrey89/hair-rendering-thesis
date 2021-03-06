from mpl_toolkits import mplot3d

import numpy as np
import matplotlib.pyplot as plt
import sys

if (len(sys.argv) < 2):
    print("Specified too little arguments, provide input text file\n")

data = np.array([])

ab_thetai = []
ab_thetar = []
ab_phii = []
ab_phir = []
ab_responses = []

af_thetai = []
af_thetar = []
af_phii = []
af_phir = []
af_responses = []

af_thetad = []
af_thetad_responses = []

ab_thetad = []
ab_thetad_responses = []


# with open("./lookup/ab_attenuation_-0.428399.txt", "r") as f:
#     lines = f.read().splitlines()
#     for line in lines:
#         l = line.split(" ")
#         ab_thetai.append(float(l[0]))
#         ab_phii.append(float(l[1]))
#         ab_thetar.append(float(l[2]))
#         ab_phir.append(float(l[3]))
#         ab_responses.append(float(l[4]))

with open("./lookup/af_attenuation_1.468439.txt", "r") as f:
    lines = f.read().splitlines()
    for line in lines:
        l = line.split(" ")
        af_thetai.append(float(l[0]))
        af_phii.append(float(l[1]))
        af_thetar.append(float(l[2]))
        af_phir.append(float(l[3]))
        af_responses.append(float(l[4]))

with open("./lookup/af.txt", "r") as f:
    lines = f.read().splitlines()
    for line in lines:
        l = line.split(" ")
        af_thetad.append(float(l[0]))
        af_thetad_responses.append(float(l[1]))

with open("./lookup/ab.txt", "r") as f:
    lines = f.read().splitlines()
    for line in lines:
        l = line.split(" ")
        ab_thetad.append(float(l[0]))
        ab_thetad_responses.append(float(l[1]))






#X, Y = np.meshgrid(x, y)
#Z = f(X, Y)

fig = plt.figure()
# axs0 = fig.add_subplot(3, 2, 1, projection='3d')
# axs0.plot_trisurf(ab_thetar, ab_phir, ab_responses, cmap='viridis', edgecolor='none');
# axs0.set_xlabel(r'$\theta_r$')
# axs0.set_ylabel(r'$\phi_r$')
# axs0.set_zlabel('y')
# axs0.view_init(60, 35)

# axs1 = fig.add_subplot(3, 2, 2, projection='3d')
# z = np.ones(len(ab_thetai))
# axs1.scatter(ab_thetai, ab_phii, z, c=z, cmap='viridis', linewidth=0.5);
# axs1.set_xlabel(r'$\theta_i$')
# axs1.set_ylabel(r'$\phi_i$')
# axs1.set_zlabel('y')
# axs1.view_init(60, 35)

axs2 = fig.add_subplot(3, 2, 3, projection='3d')
axs2.plot_trisurf(af_thetar, af_phir, af_responses, cmap='viridis', edgecolor='none');
axs2.set_xlabel(r'$\theta_r$')
axs2.set_ylabel(r'$\phi_r$')
axs2.set_zlabel('y')
axs2.view_init(60, 35)

axs3 = fig.add_subplot(3, 2, 4, projection='3d')
z = np.ones(len(af_thetai))
axs3.scatter(af_thetai, af_phii, z, c=z, cmap='viridis', linewidth=0.5);
axs3.set_xlabel(r'$\theta_i$')
axs3.set_ylabel(r'$\phi_i$')
axs3.set_zlabel('y')
axs3.view_init(60, 35)


axs4 = fig.add_subplot(3,2, 5);
axs4.plot(af_thetad, af_thetad_responses);
axs4.set_xlabel(r'$\theta_d$')
axs4.set_ylabel(r'$y$')

axs5 = fig.add_subplot(3,2, 6);
axs5.plot(ab_thetad, ab_thetad_responses);
axs5.set_xlabel(r'$\theta_d$')
axs5.set_ylabel(r'$y$')


plt.show()