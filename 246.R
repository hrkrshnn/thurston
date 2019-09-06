source("poincare.R")

outs <- read.csv(paste("out/", 246, ".txt", sep=""))
xs <- outs[[1]]
ys <- outs[[2]]


z1 <- 0.5 + sqrt(3)*0.5*1i
z2 <- -0.5 + sqrt(3)*0.5*1i
y1 <- Im(toDiscModel(z1))
y2 <- Im(toDiscModel(z2))

## (1, 0), (0, y1), (0, y2)

plot(c(), xlim=c(-1, 1), ylim=c(-1, 1), asp=1)
drawCircle()
points(xs, ys, cex=0.5, col="blue")
grid()
drawGeodesic(1, 0, 0, y1)
drawGeodesic(1, 0, 0, y2)
drawGeodesic(0, y1, 0, y2)



