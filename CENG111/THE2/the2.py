a=input()
birinci=(a[0])
ikinci=(a[1])
ucuncu=(a[2])
dorduncu=(a[3])
besinci=(a[5])
if besinci=="X":
    besinci="10"
if birinci !="?" and ikinci !="?" and ucuncu !="?" and dorduncu !="?" and besinci !="?":
    check0=(int(birinci)*2+int(ikinci)*3)
    check01=(int(ucuncu)*5+int(dorduncu)*7)
    checksum=check0+check01
    if checksum%11==int(besinci):
        print("VALID")
    else:
        print("INVALID")
if birinci=="?":
    birincicheck1=(int(ikinci)*3+int(ucuncu)*5+int(dorduncu)*7)%11
    deger1=(int(besinci)-birincicheck1)%11
    newbirinci=((deger1%2)*11+deger1)//2
    if besinci=="10":
            besinci="X"
    print(str(newbirinci) + ikinci + ucuncu + dorduncu + "-" + besinci)
if ikinci=="?":
    ikincicheck1=(int(ucuncu)*5+int(birinci)*2+int(dorduncu)*7)%11
    deger2=(int(besinci)-ikincicheck1)%11
    deger2mod=deger2%3
    newikinci=(((deger2mod)*11+deger2)//3)%11
    if besinci=="10":
            besinci="X"
    print(birinci + str(newikinci) + ucuncu + dorduncu + "-" + besinci)
if ucuncu=="?":
    ucuncucheck1=(int(ikinci)*3+int(birinci)*2+int(dorduncu)*7)%11
    deger3=(int(besinci)-ucuncucheck1)%11
    deger3mod=deger3%5
    newucuncu=(((5-deger3mod)*11+deger3)//5)%11
    if besinci=="10":
            besinci="X"
    print(birinci + ikinci + str(newucuncu) + dorduncu + "-" + besinci)
if dorduncu=="?":
    dorduncucheck1=(int(ikinci)*3+int(ucuncu)*5+int(birinci)*2)%11
    deger4=(int(besinci)-dorduncucheck1)%11
    eklenecek=(((((7-(2*deger4))%7)*11)+deger4)//7)%11
    if besinci=="10":
        besinci="X"
    print(birinci + ikinci + ucuncu + str(eklenecek) + "-" + besinci)
if besinci=="?":
    check=(int(birinci)*2)+(int(ikinci)*3)
    check1=(int(ucuncu)*5)+(int(dorduncu)*7)
    check3=(check+check1)%11
    if (check3)%11== 10:
        print(birinci+ikinci+ucuncu+dorduncu+"-"+"X")
    else:
        print(birinci+ikinci+ucuncu+dorduncu+"-"+str(check3))