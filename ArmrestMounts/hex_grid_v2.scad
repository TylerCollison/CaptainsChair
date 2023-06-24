/* Hex Hole Grid V2
M_D_K 2019
Usage:
hex_grid(
   hole diameter,
   space between holes,
   thickness,
   number of columns,
   num of rows);
example:
hex_grid(3,2,1,12,10);
*/
module hex_grid(hs,sp,th,col,row){
$fn=12;//increase results in longer render time
hsp=hs+sp;
q=cos(30);
xa=(col-1)*hsp*q+hsp;
ya=(row-.5)*hsp+hsp;
echo("grid size",xa,ya);
difference(){
translate([-hsp/2,-hsp/2,0]) 
cube([xa,ya,th]);   
union(){   
   translate([0,0,-0.1])
   for(j=[0:col-1]){
     translate([hsp*j*q,(j%2)*0.5*hsp,0])
      for(i=[0:row-1]){
        translate([0,i*hsp,0]) cylinder(d=hs,h=th+0.2);
      }
     }
  }
}
}