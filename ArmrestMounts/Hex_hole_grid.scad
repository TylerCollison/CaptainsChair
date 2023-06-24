//hex hole grid
//M_D_K 2019
rd=1.5; //hole radius
s=1; //space between holes
th=0.5; //grid thickness
col=10; //columns
row=6; // double rows
//
//maths
$fn=12;
ht=th+.2;
sx=(2*rd)+s;
sy=sx*cos(30);
difference() {
translate([-rd-s,-rd-s,0])
cube([(sx*(col+0.5))+s,(sy*2*row)+(2*s)-(sy-(2*rd)),th]);
echo("size",[(sx*(col+0.5))+s,(sy*2*row)+(2*s)-(sy-(2*rd))]);

translate([0,0,-0.1])
for(y=[0:row-1]){
    translate([0,y*2*sy,0])
for(x=[0:col-1]){ 
    translate([sx*x,0,0]) cylinder(r=rd,h=ht);
    translate([(sx*x)+(sx/2),sy,0]) cylinder(r=rd,h=ht);
}
}
}