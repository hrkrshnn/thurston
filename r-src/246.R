source("poincare.R")

recursivePlot  <- function(ls, depth=1, col="black", cex=0.5){
    if(depth <= 0){
        return(c())
    }
    z1 <- ls[[1]]
    z2 <- ls[[2]]
    z3 <- ls[[3]]
    zs <- ls[[4]]

    z1t <- translation(z1)
    z2t <- translation(z2)
    z3t <- translation(z3)
    zst <- translation(zs)
    drawGeodesic(Re(z1t), Im(z1t), Re(z2t), Im(z2t))
    drawGeodesic(Re(z1t), Im(z1t), Re(z3t), Im(z3t))
    drawGeodesic(Re(z2t), Im(z2t), Re(z3t), Im(z3t))
    points(zst, cex=cex, pch=19, col=col)
    lst <- list(z1t, z2t, z3t, zst)

    z1i <- inversion(z1)
    z2i <- inversion(z2)
    z3i <- inversion(z3)
    zsi <- inversion(zs)
    drawGeodesic(Re(z1i), Im(z1i), Re(z2i), Im(z2i))
    drawGeodesic(Re(z1i), Im(z1i), Re(z3i), Im(z3i))
    drawGeodesic(Re(z2i), Im(z2i), Re(z3i), Im(z3i))
    points(zsi, cex=cex, pch=19, col=col)
    lsi <- list(z1i, z2i, z3i, zsi)

    ## The recursion
    recursivePlot(lst, depth-1, col=col, cex=0.9*cex)
    recursivePlot(lsi, depth-1, col=col, cex=0.9*cex)
}

outs <- read.csv(paste("../out/", 246, ".txt", sep=""))
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
## png("246.png")
plot(c(), xlim=c(-1, 1), ylim=c(-1, 1), asp=1, xlab=NULL, ylab=NULL, main=NULL, ann=F, axes=F)
drawCircle()
points(zs, cex=0.5, pch=19, col="blue")
## grid()
drawGeodesic(1, 0, 0, y1)
drawGeodesic(1, 0, 0, y2)
drawGeodesic(0, y1, 0, y2)
recursivePlot(list(z1, z2, z3, zs), 9, col="blue", cex=0.5)
dev.off()

