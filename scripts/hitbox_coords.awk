#Wyszukuje w .obj najbardziej wysuniętych coordów w osiach x i z
BEGIN	{punkt[0][0] = 0; punkt[0][1] = 0;
	 punkt[1][0] = 0; punkt[1][1] = 0;
	 punkt[2][0] = 0; punkt[2][1] = 0;
	 punkt[3][0] = 0; punkt[3][1] = 0;
}

#       +x
#        ^
#  1     |   3
#        |
#-z------------->+z
#        |
#  0     |   2
#        -x

$1=="v"	{ if($3>0)i=2; else i=0; #z
          if($2>0)i+=1;          #x
	  if(abs($2)>punkt[i][0])punkt[i][0]=abs($2); if(abs($3)>punkt[i][1])punkt[i][1]=abs($3);}
END	{printf("-%f,-%f %f,-%f -%f,%f %f,%f\n",punkt[0][0],punkt[0][1],punkt[1][0],punkt[1][1],punkt[2][0],punkt[2][1],punkt[3][0],punkt[3][1]);}
function abs(a) {if(a>0)return a; else return -a};
