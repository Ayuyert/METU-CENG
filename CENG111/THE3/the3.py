def forward_pass(network,X):
    import math
    anno=[]
    def relu(annoe):
        b=[]
        for valuex in annoe:
            if valuex < 0:
                b.append(0)
            else:
                b.append(valuex)
        nonlocal anno
        anno=b
    def sigmoid_clipped(annoy):
        c=[]
        for valu in annoy:
            if valu <= -700:
                c.append(0)
            elif valu > -700 and valu < 700:
                c.append(1 / (1 + (math.exp((-1*valu)))))
            else:
                c.append(1)
        nonlocal anno
        anno=c
    for dude in network:
        if type(dude)==list and dude == network[0]:
            a=0
            l=0
            f=0
            for root in dude[1]:
                for p in X:
                    eleman=p*root[l]
                    a+=eleman
                    l+=1
                    f+=1
                f=0
                anno.append(a)
                a = 0
                l=0
        elif type(dude)==list and dude != network[0]:
            a=0
            l=0
            annow=anno[:]
            anno=[]
            for root in dude[1]:
                for k in annow:
                    eleman=k*root[l]
                    a+=eleman
                    if l==len(dude[1][0])-1:
                        break
                    l+=1
                l=0
                anno.append(a)
                a=0
        elif type(dude)== str and dude.startswith("relu"):
            relu(anno)
        elif type(dude) == str and dude.startswith("sigmoid"):
            sigmoid_clipped(anno)
    return anno