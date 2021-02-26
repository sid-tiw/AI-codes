% Total randomness of the image. The hypothesis is that more the sudden
% change in the color of the neighbouring pixels on the separation of the blocks, more entropy the image
% has. The objective to minimize the entropy.

function [entropy] = total_entropy(img)
vec = img(:, :, 1) + img(:, :, 2) + img(:, :, 3);
px = gradient(vec);
entropy = sum(sum(abs(px)));