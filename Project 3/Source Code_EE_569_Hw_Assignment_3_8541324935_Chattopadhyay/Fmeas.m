edgesDemo

%% Ground Truth Labeling
gt= load('D:\Image Processing\EE569_hw3_images\Animal.mat');
a.groundTruth{1,1} = gt.groundTruth{1};
[thr1 cntR1 sumR1 cntP1 sumP1 V1] = edgesEvalImg(E,a);
P1 = cntP1./sumP1;
R1 = cntR1./sumR1;
F1 = 2*(P1.*R1)./(P1+R1);

a.groundTruth{1,1} = gt.groundTruth{2};
[thr1 cntR2 sumR2 cntP2 sumP2 V2] = edgesEvalImg(E,a);
P2 = cntP2./sumP2;
R2 = cntR2./sumR2;
F2 = 2*(P2.*R2)./(P2+R2);

a.groundTruth{1,1} = gt.groundTruth{3};
[thr1 cntR3 sumR3 cntP3 sumP3 V3] = edgesEvalImg(E,a);
P3 = cntP3./sumP3;
R3 = cntR3./sumR3;
F3 = 2*(P3.*R3)./(P3+R3);

a.groundTruth{1,1} = gt.groundTruth{4};
[thr1 cntR4 sumR4 cntP4 sumP4 V4] = edgesEvalImg(E,a);
P4 = cntP4./sumP4;
R4 = cntR4./sumR4;
F4 = 2*(P4.*R4)./(P4+R4);

a.groundTruth{1,1} = gt.groundTruth{5};
[thr1 cntR5 sumR5 cntP5 sumP5 V5] = edgesEvalImg(E,a);
P5 = cntP5./sumP5;
R5 = cntR5./sumR5;
F5 = 2*(P5.*R5)./(P5+R5);

a.groundTruth{1,1} = gt.groundTruth{3};
[thr1 cntR3 sumR3 cntP3 sumP3 V3] = edgesEvalImg(E,a);
P3 = cntP3./sumP3;
R3 = cntR3./sumR3;
F3 = 2*(P3.*R3)./(P3+R3);