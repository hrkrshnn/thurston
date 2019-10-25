source("poincare.R")

outs <- read.csv(paste("out/", 246, ".txt", sep=""))
xs <- outs[[1]]
ys <- outs[[2]]
zs <- c()
for(i in 0:length(xs)){
    zs <- c(zs, xs[i] + 1i*ys[i])
}

z1 <- 0.5 + sqrt(3)*0.5*1i
z2 <- -0.5 + sqrt(3)*0.5*1i
z3 <- 1
y1 <- Im(toDiscModel(z1))
y2 <- Im(toDiscModel(z2))
z1 <- toDiscModel(z1)
z2 <- toDiscModel(z2)


## (1, 0), (0, y1), (0, y2)
pdf("246.pdf", width=7, height=7)
plot(c(), xlim=c(-1, 1), ylim=c(-1, 1), asp=1, xlab=NULL, ylab=NULL, main=NULL, ann=F, axes=F)
drawCircle()
points(zs, cex=0.5, col="blue")
## grid()
drawGeodesic(1, 0, 0, y1)
drawGeodesic(1, 0, 0, y2)
drawGeodesic(0, y1, 0, y2)
recursivePlot(list(z1, z2, z3, zs), 9, col="blue", cex=0.5)
dev.off()

