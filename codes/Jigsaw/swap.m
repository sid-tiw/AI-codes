% Swap the ithe block with the jth block. I and J both must be between 0
% and n^2 - 1

% tot - the total number of the blocks in one row or one column
% img - the image array
% i, j - the positions of the blocks to swap

function [img] = swap(img, i, j, sz, tot)
temp_block1 = img(fix(i/tot) * sz + 1 : fix(i/tot) * sz + sz, mod(i, tot) * sz + 1 : mod(i, tot) * sz + sz, :);
temp_block2 = img(fix(j/tot) * sz + 1 : fix(j/tot) * sz + sz, mod(j, tot) * sz + 1 : mod(j, tot) * sz + sz, :);

img(fix(i/tot) * sz + 1 : fix(i/tot) * sz + sz, mod(i, tot) * sz + 1 : mod(i, tot) * sz + sz, :) = temp_block2;
img(fix(j/tot) * sz + 1 : fix(j/tot) * sz + sz, mod(j, tot) * sz + 1 : mod(j, tot) * sz + sz, :) = temp_block1;