H=[1 0 0 0 0 1 0 1 0 1 0 0;
   1 0 0 1 1 0 0 0 0 0 1 0;
   0 1 0 0 1 0 1 0 1 0 0 0;
   0 0 0 1 0 1 0 0 0 0 1 1;
   0 0 0 1 0 0 1 1 0 0 0 1;
   0 1 0 0 1 0 0 0 1 0 1 0;
   1 0 0 1 0 0 1 0 0 1 0 0;
   0 1 0 0 0 1 0 1 0 1 0 0;
   0 0 1 1 0 0 0 0 1 0 0 1];

%load H.mat
 prob=0:0.1:1;
 success=zeros(1,length(prob));
 ee=1;
length=size(H,2)
row=size(H,1)
Nsim=10000;
for d=prob
    for N=1:Nsim
        message_enterd=zeros(1,length);
        noise=rand(1,length)>1-d;
        %rec=[0 0 1 0 0 1 0 0 0 0 0 1];
        %rec=ones(1,col)
        message=xor(message_enterd,noise);
        for it= 1:50
            temp=message;
            for i=1:length
                beta=zeros(1,length);
                count=1;
                for j=1:row
                    beta(1)=message(i);
                    if(H(j,i)==1)
                        count=count+1;
                        sum=0;
                        for k=1:length
                            if(H(j,k)==1 && k~=i)
                                sum=sum+message(k);
                            end
                        end
                        sum=mod(sum,2);
                        beta(count)=sum;
                    end
                end
                binc=zeros(1,2);
                for t=1:count+1
                    if(beta(t)==0)
                        binc(1)=binc(1)+1;
                    else
                        binc(2)=binc(2)+1;
                    end
                end
                if(binc(2)==binc(1))
                    if(beta(1)==0)
                        temp(i)=1;
                    else
                        temp(i)=0;
                    end
                elseif(binc(2)>binc(1))
                    temp(i)=1;
                elseif(binc(1)>binc(2))
                    temp(i)=0;
                   
                end
               message=temp;
            end
             
            if(message==0)
                success(ee)=success(ee)+1;
                break;
            end
        end
        
    end
    ee=ee+1;
end
%suc/1000

plot(prob,success/N);
title('Hard decision over BSC(Hmatrix)');
xlabel('probability');
ylabel('decoding capability');