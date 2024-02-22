def inheritance(infos):
    gari=[]
    liste=[]
    children=[]
    anno=[]
    indo=list(infos)

    for t in indo:

        a=t.split()
        anno.append(a)

    for g in anno:
        if g[0]=="DECEASED":
            dead=g[1]
            miras=g[2]
    miras=float(miras)

    newmiras=miras
    bolucu=0
    def desfind(chil,ary):
        anan=[]
        for deneme in ary:
            if deneme[0] == "CHILD" and len(deneme) >= 3 and (deneme[1] == chil or deneme[2] == chil):
                anan.append(31)
        if anan is not []:
            return True
        else:
            return False
    def cocukbulan(orr,ary,kesir):

        soyy=[]
        nonlocal liste
        carpan=[]
        nonlocal anno
        nonlocal bolucu
        bolut=kesir
        if ["DEPARTED"] + [orr] in anno:
            if isgreen(orr,anno)==True:
                for pos in ary:
                    if pos[0] == "CHILD" and len(pos) >= 3 and (pos[1] == orr or pos[2] == orr):
                        soyy += pos[3:]

                for ana in soyy:
                    if isgreen(ana,anno)==True:
                        carpan.append(ana)

                bolut=bolut*len(carpan)

                for dud in carpan:

                    if ["DEPARTED"] + [dud] not in anno:
                        if (dud,newmiras/bolut) not in liste:

                            liste +=[(dud,newmiras/bolut)]
                    else:
                        for knk in soyy:
                            if ["DEPARTED"] + [knk] in anno:

                                cocukbulan(knk, anno,bolut)

    def isgreen(eleman,ann):
        soy=[]
        a=False
        nonlocal anno
        if type(eleman)==str:
            eleman=[eleman]

        if type(eleman) == list:

            for kisi in eleman:
                if ["DEPARTED"]+[kisi] not in anno:
                    return True
                else:
                    if desfind(kisi,anno)==True:

                        for po in anno:
                            if po[0] == "CHILD" and len(po) >= 3 and (po[1] == kisi or po[2] == kisi):

                                soy += po[3:]


                        a=isgreen(soy,anno)
                        if a==True:
                            return True
        if a== True:
            return True
        return False
    if isgreen(dead,anno)==True:
        for p in anno:
            if p[0]=="MARRIED":
                if p[2]==dead:
                    gari=p[1]
                    kariyer = miras * 0.25
                    newmiras=miras-kariyer
                    liste += [(gari, kariyer)]
                    for olu in anno:
                        if olu[0]=="DEPARTED" and olu[1]==gari and [(gari, kariyer)] in liste:
                            liste.remove((gari, kariyer))
                            newmiras=miras
                    for olu in anno:
                        if olu[0] == "DEPARTED" and olu[1] == gari:
                            liste.remove((gari,kariyer))
                            newmiras = miras

                elif p[1] == dead:
                    gari = p[2]
                    kariyer = miras * 0.25
                    newmiras=miras-kariyer
                    liste+=[(gari,kariyer)]
                    for olu in anno:
                        if olu[0]=="DEPARTED" and olu[1]==gari:
                            liste.remove((gari, kariyer))
                            newmiras=miras
        for y in anno:
            if y[0] == "CHILD" and len(y) >= 3 and (y[1] == dead or y[2] == dead):
                children += y[3:]

        bolucu=0
        for cocuk in children:
            if ["DEPARTED"]+[cocuk] not in anno:
                bolucu +=1

            if ["DEPARTED"]+[cocuk] in anno:
                if isgreen(cocuk,anno)==True:
                    bolucu+=1
                else:
                    bolucu=bolucu
        bolen=bolucu

        for cocuk in children:
            if ["DEPARTED"]+[cocuk] not in anno:
                liste+=[(cocuk,newmiras/bolen)]
            if ["DEPARTED"]+[cocuk] in anno:
                if isgreen(cocuk,anno)==True:
                    cocukbulan(cocuk,anno,bolucu)

    else:

        parents=[]

        for p in anno:
            if p[0]=="MARRIED":
                if p[2]==dead:
                    gari=p[1]
                    kariyer = miras * 0.5
                    newmiras=miras-kariyer
                    liste += [(gari, kariyer)]
                    for olu in anno:
                        if olu[0] == "DEPARTED" and olu[1] == gari:
                            liste.remove((gari,kariyer))
                            newmiras = miras

                elif p[1] == dead:
                    gari = p[2]
                    kariyer = miras * 0.5
                    newmiras = miras - kariyer
                    liste += [(gari, kariyer)]
                    for olu in anno:
                        if olu[0] == "DEPARTED" and olu[1] == gari:
                            liste.remove((gari,kariyer))
                            newmiras = miras
        for a in anno:
            if a[0]=="CHILD" and dead in a[3:]:
                parents = a[1:3]

        if parents !=[]:
            if ["DEPARTED"]+[parents[0]] not in anno and ["DEPARTED"]+[parents[1]] not in anno:
                newmiras=newmiras/2
                liste+=[(parents[0],newmiras)]+[(parents[1],newmiras)]

            if ["DEPARTED"]+[parents[0]] not in anno and ["DEPARTED"]+[parents[1]] in anno:
                bolucu=1
                if isgreen(parents[1],anno)==False:
                    liste+=[(parents[0],newmiras)]
                else:

                    liste+=[(parents[0],newmiras/2)]
                    newmiras=newmiras/2
                    childrenss=[]
                    for y in anno:
                        if y[0] == "CHILD" and len(y) >= 3 and (y[1] == parents[1] or y[2] == parents[1]):
                            childrenss += y[3:]
                    for yavru in childrenss:
                        if isgreen(yavru,anno)==True:
                            bolucu+=1
                    bolucu=bolucu-1

                    for cocuk in childrenss:
                        if ["DEPARTED"] + [cocuk] not in anno:
                            liste += [(cocuk, newmiras / bolucu)]
                        if ["DEPARTED"] + [cocuk] in anno:
                            if isgreen(cocuk, anno) == True:
                                cocukbulan(cocuk, anno,bolucu)

            if ["DEPARTED"] + [parents[1]] not in anno and ["DEPARTED"] + [parents[0]] in anno:


                bolucu=1

                if isgreen(parents[0], anno) == False:
                    liste += [(parents[1], newmiras)]
                else:

                    liste += [(parents[1], newmiras / 2)]
                    newmiras = newmiras /2

                    cocukbulan(parents[0], anno,bolucu)
            if ["DEPARTED"] + [parents[0]] in anno and ["DEPARTED"] + [parents[1]] in anno and (isgreen(parents[1],anno)==True or isgreen(parents[0],anno)==True):

                bolucu=0
                childre1=[]
                childre2=[]
                for y in anno:
                    if y[0] == "CHILD" and len(y) >= 3 and (y[1] == parents[0] or y[2] == parents[0]):
                        childre1 += y[3:]

                for y in anno:
                    if y[0] == "CHILD" and len(y) >= 3 and (y[1] == parents[1] or y[2] == parents[1]) :
                        childre2 += y[3:]

                if isgreen(parents[1],anno)==True and isgreen(parents[0],anno)==True:
                    newmiras=newmiras/2


                    for velet in childre1:
                        if ["DEPARTED"]+[velet] not in anno:
                            bolucu+=1
                        else:
                            if isgreen(velet,anno)==True:
                                bolucu+=1
                    for cocuk in childre1:
                        if ["DEPARTED"] + [cocuk] not in anno:
                            liste += [(cocuk, newmiras / bolucu)]
                        if ["DEPARTED"] + [cocuk] in anno:
                            if isgreen(cocuk, anno) == True:
                                cocukbulan(cocuk, anno, bolucu)
                    bolucu=0
                    for velet in childre2:
                        if ["DEPARTED"]+[velet] not in anno:
                            bolucu+=1
                        else:
                            if isgreen(velet,anno)==True:
                                bolucu+=1
                    for cocuk in childre2:

                        if ["DEPARTED"] + [cocuk] not in anno:

                            liste += [(cocuk, newmiras / bolucu)]
                        if ["DEPARTED"] + [cocuk] in anno:
                            if isgreen(cocuk, anno) == True:
                                cocukbulan(cocuk, anno, bolucu)

                if isgreen(parents[0], anno) == True and isgreen(parents[1],anno)==False:


                    for velet in childre1:
                        if ["DEPARTED"]+[velet] not in anno:
                            bolucu+=1
                        else:
                            if isgreen(velet,anno)==True:
                                bolucu+=1
                    for cocuk in childre1:
                        if ["DEPARTED"] + [cocuk] not in anno:
                            liste += [(cocuk, newmiras / bolucu)]
                        if ["DEPARTED"] + [cocuk] in anno:
                            if isgreen(cocuk, anno) == True:
                                cocukbulan(cocuk, anno, bolucu)

                if isgreen(parents[1], anno) == True and isgreen(parents[0], anno) == False:

                    for velet in childre2:
                        if ["DEPARTED"] + [velet] not in anno:
                            bolucu += 1
                        else:
                            if isgreen(velet, anno) == True:
                                bolucu += 1
                    for cocuk in childre2:
                        if ["DEPARTED"] + [cocuk] not in anno:
                            liste += [(cocuk, newmiras / bolucu)]
                        if ["DEPARTED"] + [cocuk] in anno:
                            if isgreen(cocuk, anno) == True:
                                cocukbulan(cocuk, anno, bolucu)


            if ["DEPARTED"] + [parents[0]] in anno and ["DEPARTED"] + [parents[1]] in anno and isgreen(parents[1],anno)==False and isgreen(parents[0],anno)==False:
                if (gari,miras/2) in liste:
                    liste.remove((gari,miras/2))
                bolucu = 1

                for p in anno:
                    if p[0] == "MARRIED":
                        if p[2] == dead:
                            gari = p[1]
                            kariyer = miras * 0.75
                            newmiras = miras - kariyer
                            liste += [(gari, kariyer)]
                            for olu in anno:
                                if olu[0] == "DEPARTED" and olu[1] == gari:
                                    liste.remove((gari, kariyer))
                                    newmiras = miras

                        elif p[1] == dead:
                            gari = p[2]
                            kariyer = miras * 0.75
                            newmiras = miras - kariyer
                            liste += [(gari, kariyer)]
                            for olu in anno:
                                if olu[0] == "DEPARTED" and olu[1] == gari:
                                    liste.remove((gari, kariyer))
                                    newmiras = miras
                if isgreen(parents[0],anno)==False and isgreen(parents[1],anno)==False:
                    annebuyuk=[]
                    bababuyuk=[]
                    for aranan in anno:
                        if aranan[0]== "CHILD" and parents[0] in aranan[3:]:
                            annebuyuk+=aranan[1:3]
                        if aranan[0]=="CHILD" and parents[1] in aranan[3:]:
                            bababuyuk+=aranan[1:3]

                    if annebuyuk is not []:
                        if isgreen(bababuyuk,anno)==True and isgreen(annebuyuk,anno)==True:
                            newmiras=newmiras/2
                        nenesayar=[]
                        bolucu=0
                        for nene in annebuyuk:

                            if ["DEPARTED"] + [nene] not in anno:

                                bolucu += 1
                                nenesayar += [nene]
                            else:

                                if isgreen(nene, anno) == True:
                                    nenesayar += [nene]
                                    bolucu += 1

                        for sans in nenesayar:
                            if ["DEPARTED"] + [sans] not in anno:
                                liste += [(sans, newmiras / bolucu)]
                            if ["DEPARTED"] + [sans] in anno:
                                if isgreen(sans, anno) == True:
                                    cocukbulan(sans, anno, bolucu)

                    if bababuyuk is not []:
                        dedesayar=[]
                        bolucu=0
                        for dede in bababuyuk:

                            if ["DEPARTED"]+[dede] not in anno:

                                bolucu +=1
                                dedesayar+=[dede]
                            else:

                                if isgreen(dede,anno)==True:
                                    dedesayar+=[dede]

                                    bolucu += 1

                        for sans in dedesayar:
                            if ["DEPARTED"] + [sans] not in anno:
                                liste += [(sans, newmiras / bolucu)]
                            if ["DEPARTED"] + [sans] in anno:
                                if isgreen(sans, anno) == True:
                                    cocukbulan(sans, anno, bolucu)

    if len(liste)==1 and liste[0][0]==gari:
        liste=[(gari,miras)]


    kisilist =[]
    sonuclist=[]
    bonuskisi=""
    bonus=0
    genelist=[]
    eklenen=[]
    ekleme=[]
    for uye in liste:
        if uye[0] not in kisilist:
            kisilist.append(uye[0])
            sonuclist.append(uye[1])
        else:
            bonuskisi = uye[0]
            bonus = uye[1]
            genelist+=[(uye[0],uye[1])]
    for i in genelist:
        bonuskisi=i[0]
        bonus=i[1]
        if (bonuskisi,bonus) in liste:
            liste.remove((bonuskisi,bonus))

            eklenen+=[i[0]]
            ekleme+=[bonus]

    for j in eklenen:
        for k in liste:
            if type(k)!=list:
                k=list(k)

            if j==k[0]:
                point=k[1]

                if (k[0],k[1]) in liste:
                    liste.remove((k[0],k[1]))
                    sil=ekleme[eklenen.index(j)]
                    if len(liste) >1 and len(genelist)>=1:
                        k[1]=k[1]-sil/2
                        liste+=[(k[0],k[1]+ekleme[eklenen.index(j)])]
                    else:
                        liste += [(k[0], k[1] + ekleme[eklenen.index(j)])]
    kap=0
    for son in liste:
        kap+=son[1]

    if abs(kap-miras)>0.0001 and liste!=[]:
        bos=[]
        listem=[]
        carpan=miras/kap
        for u in liste:
            bos.append(u[1]*carpan)

        for a in liste:
            listem.append((a[0],a[1]*carpan))
        liste=listem

    return liste
