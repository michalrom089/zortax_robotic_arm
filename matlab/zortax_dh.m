syms theta1 theta2 theta3 d1 a2 a3 a4

const=sqrt(2)/2;

T_0_1=[cos(theta1) -sin(theta1) 0 0 ;sin(theta1) cos(theta1) 0 0 ; 0 0 1 d1 ; 0 0 0 1];
T_1_2=[cos(theta2-pi/2) -sin(theta2-pi/2) 0 0;0 0 1 0;-sin(theta2-pi/2) -cos(theta2-pi/2) 0 0;0 0 0 1];
T_2_3=[cos(theta3+pi/2) -sin(theta3+pi/2) 0 a2;sin(theta3+pi/2) cos(theta3+pi/2) 0 0;0 0 1 0;0 0 0 1];
T_3_4=[const -const 0 a3;const const 0 0 ;0 0 1 0;0 0 0 1];
T_4_5=[1 0 0 a4;0 1 0 0;0 0 1 0;0 0 0 1];

T=T_0_1*T_1_2*T_2_3*T_3_4*T_4_5;


x=simplify(T(1,4))
y=simplify(T(2,4))
z=simplify(T(3,4))
