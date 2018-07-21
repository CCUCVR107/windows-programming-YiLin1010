clear all;
I = imread('image.jpg');
img = rgb2gray(I); %24 2 8bit
[height, width] = size(img);

[counts, x] = imhist(img);
location = find(counts ~= 0); %find non-zero degrees
minCdf = counts(1);

imgEqual = img;

for i = 1:length(location)
    CDF = sum(counts(1:location(i)));
    degree = round((CDF - minCdf) * 255 / (height *width - minCdf));
    p = find(img == x(i));
    imgEqual(p) = degree;
end

% original
figure, imshow(img);
title('Original image');
histOriginal = figure;
imhist(img);
title('Original histogram');

% equalization
figure, imshow(imgEqual);
title('Equalization image');
histEqual = figure;
imhist(imgEqual);
title('Equalization histogram');

imwrite(imgEqual, 'imageEqualization.jpg');
saveas(histOriginal, 'imageOriginalHistogram.jpg');
saveas(histEqual, 'imageEqualizationHistogram.jpg');

