kalman <- function(vx,vy,vz,duration, measnoise, accelnoise,g,step) {
  T = step 
  R = matrix(c(measnoise^2, 0, 0,
               0, measnoise^2, 0,
               0, 0, measnoise^2),nrow=3,ncol=3,byrow=TRUE)   
  Q = matrix(c(0, 0, 0, 0, 0, 0,
               0, (accelnoise *(T^2/2))^2, 0, 0, accelnoise *(T*(T^2/2)), 0,
               0, 0, 0, 0, 0, 0,
               0, 0, 0, 0, 0, 0,
               0, accelnoise *(T*(T^2/2)), 0, 0, (accelnoise *T)^2, 0,
               0, 0, 0, 0, 0, 0),nrow=6,ncol=6,byrow=TRUE)
  A = matrix(c(1, 0, 0, T, 0, 0,
               0, 1, 0, 0, T, 0,
               0, 0, 1, 0, 0, T,
               0, 0, 0, 1, 0, 0,
               0, 0, 0, 0, 1, 0,
               0, 0, 0, 0, 0, 1),nrow=6,ncol=6,byrow=TRUE)         
  B = matrix(c(0, -T^2/2, 0, 0, -T, 0),nrow=6,ncol=1,byrow=TRUE)  
  H = matrix(c(1, 0, 0, 0, 0, 0,
               0, 1, 0, 0, 0, 0,
               0, 0, 1, 0, 0, 0),nrow=3,ncol=6,byrow=TRUE)      
  
  P = Q
  
  x=matrix(c(0,0,0,vx,vy,vz),nrow=6,ncol=1)
  xhat=x
  

  I = diag(6)
  
  pos = matrix(rep(0,3*duration),nrow=duration,ncol=3)                
  poshat = matrix(rep(0,3*duration),nrow=duration,ncol=3)            
  posmeas = matrix(rep(0,3*duration),nrow=duration,ncol=3)         

  for(t in 0:duration){
    x=A%*%x+B*g+accelnoise*matrix(c(0, T^2/2*runif(1, -1.0, 1.0), 0, 0, T*runif(1, -1.0, 1.0), 0),nrow=6,ncol=1,byrow=TRUE) 
    z=H%*%x+measnoise*matrix(c(0, T^2/2*runif(1, -1.0, 1.0), 0),nrow=3,ncol=1,byrow=TRUE)
    xhat=A%*%xhat+B*g
    P=A%*%P%*%t(A)+Q
    K=P%*%t(H)%*%solve(H%*%P%*%t(H)+R)
    xhat=xhat+K%*%(z-H%*%xhat)
    P = (I-K%*%H)%*%P
    pos[t,1]=x[1]
    pos[t,2]=x[2]
    pos[t,3]=x[3]
    
    posmeas[t,1]=z[1]
    posmeas[t,2]=z[2]
    posmeas[t,3]=z[3]
    
    poshat[t,1]=xhat[1]
    poshat[t,2]=xhat[2]
    poshat[t,3]=xhat[3]
    
    t=t+1
  }
  return (list("pos"=pos,"poshat"=poshat,"posmeas"=posmeas))
}

vx=20
vy=40
vz=10
measnoise=3000
accelnoise=3.1
g=10
step=0.1
duration=2*vy/(g*step)
l=kalman(vx,vy,vz,duration,measnoise,accelnoise,g,step)

pos=l[1]

plot(l$pos[,1])
plot(l$pos[,2])

plot(l$pos[,2], type="o", col="blue", ylim=c(0,100))
lines(l$poshat[,2], type="o", col="green")
lines(l$posmeas[,2], type="o", col="red")
