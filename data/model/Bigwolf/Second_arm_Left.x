xof 0302txt 0064
template Header {
 <3D82AB43-62DA-11cf-AB39-0020AF71E433>
 WORD major;
 WORD minor;
 DWORD flags;
}

template Vector {
 <3D82AB5E-62DA-11cf-AB39-0020AF71E433>
 FLOAT x;
 FLOAT y;
 FLOAT z;
}

template Coords2d {
 <F6F23F44-7686-11cf-8F52-0040333594A3>
 FLOAT u;
 FLOAT v;
}

template Matrix4x4 {
 <F6F23F45-7686-11cf-8F52-0040333594A3>
 array FLOAT matrix[16];
}

template ColorRGBA {
 <35FF44E0-6C7C-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
 FLOAT alpha;
}

template ColorRGB {
 <D3E16E81-7835-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
}

template IndexedColor {
 <1630B820-7842-11cf-8F52-0040333594A3>
 DWORD index;
 ColorRGBA indexColor;
}

template Boolean {
 <4885AE61-78E8-11cf-8F52-0040333594A3>
 WORD truefalse;
}

template Boolean2d {
 <4885AE63-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template MaterialWrap {
 <4885AE60-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template TextureFilename {
 <A42790E1-7810-11cf-8F52-0040333594A3>
 STRING filename;
}

template Material {
 <3D82AB4D-62DA-11cf-AB39-0020AF71E433>
 ColorRGBA faceColor;
 FLOAT power;
 ColorRGB specularColor;
 ColorRGB emissiveColor;
 [...]
}

template MeshFace {
 <3D82AB5F-62DA-11cf-AB39-0020AF71E433>
 DWORD nFaceVertexIndices;
 array DWORD faceVertexIndices[nFaceVertexIndices];
}

template MeshFaceWraps {
 <4885AE62-78E8-11cf-8F52-0040333594A3>
 DWORD nFaceWrapValues;
 Boolean2d faceWrapValues;
}

template MeshTextureCoords {
 <F6F23F40-7686-11cf-8F52-0040333594A3>
 DWORD nTextureCoords;
 array Coords2d textureCoords[nTextureCoords];
}

template MeshMaterialList {
 <F6F23F42-7686-11cf-8F52-0040333594A3>
 DWORD nMaterials;
 DWORD nFaceIndexes;
 array DWORD faceIndexes[nFaceIndexes];
 [Material]
}

template MeshNormals {
 <F6F23F43-7686-11cf-8F52-0040333594A3>
 DWORD nNormals;
 array Vector normals[nNormals];
 DWORD nFaceNormals;
 array MeshFace faceNormals[nFaceNormals];
}

template MeshVertexColors {
 <1630B821-7842-11cf-8F52-0040333594A3>
 DWORD nVertexColors;
 array IndexedColor vertexColors[nVertexColors];
}

template Mesh {
 <3D82AB44-62DA-11cf-AB39-0020AF71E433>
 DWORD nVertices;
 array Vector vertices[nVertices];
 DWORD nFaces;
 array MeshFace faces[nFaces];
 [...]
}

Header{
1;
0;
1;
}

Mesh {
 173;
 -11.85790;-15.80060;-13.02410;,
 -7.72380;-15.29045;-13.76295;,
 -9.67650;-19.38935;-14.69530;,
 -15.37620;-39.53200;-3.59490;,
 -9.85240;-29.71575;-11.26490;,
 -10.23945;-33.92020;-6.28645;,
 -15.65770;-14.92105;-5.91700;,
 -8.07565;-7.51485;-7.13085;,
 -13.08930;-14.00625;-10.77235;,
 -11.59400;-28.48430;-12.91855;,
 -7.95250;-25.59925;-12.76020;,
 -13.96885;-9.66110;10.30265;,
 -10.83755;-6.61770;9.12400;,
 -17.45205;-12.72200;7.59350;,
 -9.35985;-7.70835;-4.52725;,
 -12.28010;-25.03635;-14.06200;,
 -10.78480;-25.84555;-13.93885;,
 1.61745;-10.08330;-11.15935;,
 -1.30280;-7.19825;-10.47330;,
 3.57015;-7.39175;-10.42050;,
 -5.47200;-16.31080;-14.11480;,
 -22.64165;-34.39515;-7.58820;,
 -18.20850;-34.57105;-10.40290;,
 -24.18975;-38.52925;-4.82630;,
 -0.44080;-19.19585;-11.17695;,
 -18.24370;-14.56920;9.52860;,
 -21.97315;-20.30415;3.01965;,
 -17.54005;-13.39055;4.69085;,
 -18.08540;-15.92375;11.23500;,
 -20.77685;-19.68835;8.63140;,
 -11.68195;-8.20090;2.79095;,
 -10.69680;-5.73805;6.48520;,
 -6.21090;-5.52695;-7.48265;,
 -8.49785;-5.17515;-3.84115;,
 -5.64795;2.30135;-7.88730;,
 -17.15300;-36.11915;-9.03075;,
 3.27110;-21.99290;-4.73835;,
 -3.32585;-28.90650;-1.62460;,
 -19.14090;-26.61960;-11.93340;,
 -22.76480;-30.57775;-9.10110;,
 -20.65380;-23.20675;-9.66405;,
 -15.85120;-37.40340;-6.88455;,
 -21.55095;-39.86615;-5.00225;,
 -22.14910;-29.39905;10.53135;,
 -20.38985;-30.38420;12.85345;,
 -14.12725;-41.66060;-1.20240;,
 -12.20970;-37.45615;-1.25515;,
 -22.06115;-34.87010;12.62475;,
 -27.16275;-36.06635;9.35270;,
 -5.73595;-8.57035;-10.13905;,
 -4.27580;-5.68530;-9.08350;,
 -18.49000;-32.53045;14.22560;,
 -21.02320;-22.18640;-7.18360;,
 -24.61195;-29.38145;-3.99950;,
 -22.69440;-25.01875;7.48795;,
 -24.40085;-24.87800;3.21315;,
 -25.72020;-27.74545;4.93715;,
 -22.37775;-23.48825;-0.90335;,
 -16.57250;-35.69695;13.38120;,
 -15.55215;-38.45880;10.79520;,
 -12.79025;-34.88775;13.38120;,
 -24.59435;-29.45190;7.64630;,
 -16.99470;-22.20400;-12.28525;,
 -5.98220;-34.07850;2.10485;,
 -19.77420;-38.21255;12.58960;,
 -17.68075;-34.55350;13.96175;,
 -2.12960;-25.49365;-7.95765;,
 2.37390;-20.11065;-8.32710;,
 4.88950;-12.28225;-9.80480;,
 -5.33130;5.83730;-7.21880;,
 -8.11085;7.05120;-1.43110;,
 -5.87665;8.52885;-4.61520;,
 -8.11085;3.51515;-3.91155;,
 -4.41655;-25.22985;18.46525;,
 -7.97005;-26.54925;18.58840;,
 -7.47750;-29.46950;17.33935;,
 -8.33950;7.45575;0.85585;,
 -9.37745;4.92255;0.97900;,
 -8.55065;6.34750;6.11580;,
 -11.29495;-11.63140;14.29600;,
 -9.87000;-7.53250;12.13220;,
 -4.17025;12.04725;-0.85055;,
 -5.89425;10.85095;1.27805;,
 0.31565;-29.06485;4.98990;,
 -5.82390;-34.79975;7.55830;,
 -8.53305;-37.66725;4.21590;,
 -4.82115;6.96315;12.00905;,
 -4.90905;2.79395;13.52195;,
 -2.90365;6.34750;13.87380;,
 2.58500;10.21770;14.55985;,
 4.74880;8.00115;17.11065;,
 -10.43295;-17.78850;17.69120;,
 -10.96070;-22.20400;18.50040;,
 -7.24885;-14.67470;18.60595;,
 5.39970;-20.46240;-1.36070;,
 5.80430;-21.79940;1.99930;,
 -3.09715;11.66025;-4.05225;,
 -2.32310;7.64930;-8.43265;,
 -1.53150;-25.95105;16.49495;,
 0.03420;-19.93470;18.88745;,
 -6.79145;-16.69780;19.38000;,
 -7.77655;-21.79940;19.39760;,
 -1.93610;-17.52460;19.90775;,
 -10.18665;-5.50935;0.66235;,
 -14.32075;-25.00115;16.93475;,
 -10.15150;-25.45850;18.53560;,
 -0.26485;-28.37870;1.84100;,
 -0.31765;-3.45110;17.23380;,
 -0.58155;-0.84755;16.61810;,
 -3.27310;-4.11960;15.87925;,
 2.69060;-10.29440;19.90775;,
 3.99235;-4.11960;18.71155;,
 0.36840;-7.53250;19.11615;,
 -18.06775;-43.31415;-2.41625;,
 0.22770;2.79395;16.77645;,
 5.50525;5.39750;18.30690;,
 6.82460;-2.00860;18.92265;,
 6.93015;-6.40660;-10.19180;,
 -7.58305;3.60320;10.49615;,
 -11.04865;-31.89705;16.35420;,
 -9.25430;4.25405;6.62595;,
 -0.07135;10.88620;-7.14845;,
 -3.85360;2.58285;-9.27705;,
 2.49710;5.64385;-11.65195;,
 10.58930;8.51125;-13.16480;,
 -1.05650;-29.53980;11.07670;,
 -6.08780;-31.45735;14.59505;,
 -16.16790;-45.79465;-1.27275;,
 -8.99040;-37.49130;6.52040;,
 -15.34100;-17.73570;-11.54640;,
 6.17370;-14.46360;-8.36225;,
 -26.51185;-34.76455;-4.06985;,
 -26.38865;-29.76845;-1.67735;,
 5.10060;-16.24040;17.46250;,
 -10.96070;-39.98935;2.28080;,
 1.42395;-0.39020;-12.47875;,
 -9.67650;-1.28735;6.48520;,
 5.13580;-2.55395;-13.14725;,
 -1.21480;13.68330;5.18345;,
 -9.11355;-3.04650;9.47585;,
 -18.59555;-39.93660;11.58685;,
 -1.09170;11.48430;10.68965;,
 -5.15540;10.00660;8.10365;,
 -8.58575;-4.94645;11.41095;,
 -1.40830;12.97955;7.43520;,
 4.92470;-12.95075;19.01060;,
 -0.77505;13.99995;0.11700;,
 2.53220;15.23135;4.47975;,
 3.71085;15.56560;-0.12930;,
 5.80430;13.54250;12.37850;,
 10.87075;11.94170;-10.17420;,
 10.50130;14.86195;-6.76140;,
 6.80700;16.46275;-2.08200;,
 5.78670;16.11095;8.08610;,
 8.61900;-3.38075;-14.74810;,
 8.37270;0.94675;-15.18790;,
 -13.56430;-12.29980;-0.49870;,
 9.63935;-6.89915;-8.37985;,
 -12.50875;-42.69850;5.86950;,
 -11.98100;-42.99755;3.54740;,
 -14.18000;-46.35760;0.53920;,
 -21.48060;-42.75120;-3.54210;,
 -19.26405;-41.29115;-3.80600;,
 -14.26795;-41.92445;8.01570;,
 -11.57640;-39.44400;6.97780;,
 -22.14910;-40.93930;12.50160;,
 -24.06655;-31.91465;-6.07535;,
 -28.64045;-32.16095;-2.39865;,
 -27.03960;-28.78335;0.53920;,
 3.49975;-25.84555;6.50280;,
 4.62570;-24.43820;8.98325;,
 4.83675;-22.29200;12.92380;,
 10.48370;-13.19705;-4.05225;;
 
 296;
 3;0,1,2;,
 3;3,4,5;,
 3;6,7,8;,
 3;4,9,10;,
 3;11,12,13;,
 3;14,7,6;,
 3;15,2,16;,
 3;17,18,19;,
 3;16,20,10;,
 3;21,22,23;,
 3;20,1,17;,
 3;15,16,9;,
 3;20,24,10;,
 3;25,13,26;,
 3;27,26,13;,
 3;28,25,29;,
 3;30,27,31;,
 3;11,25,28;,
 3;13,31,27;,
 3;32,33,34;,
 3;4,35,9;,
 3;3,36,37;,
 3;38,39,40;,
 3;35,41,42;,
 3;38,22,39;,
 3;29,43,44;,
 3;45,3,46;,
 3;47,44,48;,
 3;18,49,50;,
 3;51,44,47;,
 3;52,40,53;,
 3;54,55,56;,
 3;6,52,57;,
 3;52,53,57;,
 3;58,59,60;,
 3;61,43,56;,
 3;38,40,62;,
 3;37,63,46;,
 3;47,64,65;,
 3;66,67,36;,
 3;17,68,20;,
 3;69,70,71;,
 3;72,70,69;,
 3;73,74,75;,
 3;76,77,78;,
 3;79,11,28;,
 3;80,11,79;,
 3;81,70,82;,
 3;81,71,70;,
 3;83,84,85;,
 3;86,87,88;,
 3;89,88,90;,
 3;82,70,76;,
 3;91,92,93;,
 3;94,95,37;,
 3;96,97,71;,
 3;71,97,69;,
 3;73,98,99;,
 3;34,50,32;,
 3;100,101,102;,
 3;14,30,103;,
 3;104,92,91;,
 3;105,92,104;,
 3;104,51,105;,
 3;106,95,83;,
 3;107,108,109;,
 3;110,111,112;,
 3;45,113,3;,
 3;76,78,82;,
 3;114,115,90;,
 3;115,114,116;,
 3;17,19,117;,
 3;100,93,92;,
 3;93,79,91;,
 3;86,118,87;,
 3;74,65,119;,
 3;120,86,78;,
 3;96,121,97;,
 3;119,75,74;,
 3;69,122,34;,
 3;121,123,97;,
 3;124,123,121;,
 3;49,0,8;,
 3;120,118,86;,
 3;80,12,11;,
 3;97,122,69;,
 3;84,125,126;,
 3;45,127,113;,
 3;51,104,44;,
 3;69,34,72;,
 3;128,60,59;,
 3;87,114,88;,
 3;129,62,40;,
 3;24,130,67;,
 3;131,132,53;,
 3;99,98,133;,
 3;63,85,134;,
 3;122,123,135;,
 3;77,70,72;,
 3;92,101,100;,
 3;136,120,77;,
 3;50,135,137;,
 3;101,92,105;,
 3;73,99,102;,
 3;73,102,74;,
 3;82,138,81;,
 3;90,88,114;,
 3;93,112,107;,
 3;118,120,139;,
 3;77,120,78;,
 3;74,101,105;,
 3;75,126,98;,
 3;100,102,112;,
 3;110,112,102;,
 3;58,140,59;,
 3;86,141,142;,
 3;78,142,82;,
 3;114,108,116;,
 3;71,81,96;,
 3;105,65,74;,
 3;107,109,93;,
 3;143,87,118;,
 3;86,89,141;,
 3;86,88,89;,
 3;142,141,144;,
 3;77,76,70;,
 3;142,138,82;,
 3;85,84,128;,
 3;136,77,103;,
 3;83,125,84;,
 3;91,44,104;,
 3;60,126,75;,
 3;102,101,74;,
 3;93,100,112;,
 3;99,145,102;,
 3;146,81,138;,
 3;60,119,58;,
 3;96,81,146;,
 3;146,147,148;,
 3;142,144,138;,
 3;141,89,149;,
 3;150,121,151;,
 3;141,149,144;,
 3;96,146,148;,
 3;138,144,147;,
 3;96,148,152;,
 3;146,138,147;,
 3;144,153,147;,
 3;151,121,152;,
 3;121,96,152;,
 3;144,149,153;,
 3;109,108,114;,
 3;50,122,135;,
 3;137,135,154;,
 3;143,114,87;,
 3;103,77,72;,
 3;154,135,155;,
 3;50,34,122;,
 3;136,139,120;,
 3;33,72,34;,
 3;135,123,155;,
 3;122,97,123;,
 3;78,86,142;,
 3;124,121,150;,
 3;14,103,33;,
 3;112,111,107;,
 3;12,143,139;,
 3;19,50,137;,
 3;12,139,31;,
 3;31,136,103;,
 3;31,139,136;,
 3;33,103,72;,
 3;109,114,143;,
 3;111,108,107;,
 3;111,116,108;,
 3;143,118,139;,
 3;13,12,31;,
 3;30,14,156;,
 3;79,109,80;,
 3;49,8,50;,
 3;80,109,143;,
 3;8,7,50;,
 3;30,31,103;,
 3;17,117,157;,
 3;18,50,19;,
 3;7,14,33;,
 3;80,143,12;,
 3;7,33,32;,
 3;7,32,50;,
 3;158,159,85;,
 3;160,45,134;,
 3;113,161,162;,
 3;159,160,134;,
 3;113,162,3;,
 3;134,45,46;,
 3;161,42,162;,
 3;163,59,140;,
 3;159,134,85;,
 3;127,45,160;,
 3;127,161,113;,
 3;158,85,164;,
 3;163,158,164;,
 3;163,164,59;,
 3;162,41,3;,
 3;162,42,41;,
 3;85,128,164;,
 3;140,58,64;,
 3;64,47,165;,
 3;164,128,59;,
 3;42,22,35;,
 3;64,58,65;,
 3;42,23,22;,
 3;134,46,63;,
 3;41,4,3;,
 3;46,3,37;,
 3;128,84,126;,
 3;23,131,21;,
 3;128,126,60;,
 3;41,35,4;,
 3;58,119,65;,
 3;21,166,39;,
 3;85,63,83;,
 3;131,166,21;,
 3;47,65,51;,
 3;35,22,9;,
 3;21,39,22;,
 3;51,65,105;,
 3;83,63,106;,
 3;60,75,119;,
 3;131,167,132;,
 3;167,168,132;,
 3;48,43,61;,
 3;166,131,53;,
 3;48,44,43;,
 3;63,37,106;,
 3;126,125,98;,
 3;4,10,67;,
 3;56,55,168;,
 3;9,16,10;,
 3;83,169,170;,
 3;4,67,66;,
 3;168,55,132;,
 3;125,171,98;,
 3;53,132,57;,
 3;83,95,169;,
 3;106,37,95;,
 3;132,55,26;,
 3;125,170,171;,
 3;9,22,15;,
 3;5,36,3;,
 3;75,98,73;,
 3;22,38,15;,
 3;5,66,36;,
 3;166,53,40;,
 3;43,54,56;,
 3;5,4,66;,
 3;166,40,39;,
 3;83,170,125;,
 3;43,29,54;,
 3;2,62,0;,
 3;40,8,129;,
 3;16,2,20;,
 3;62,129,0;,
 3;36,67,172;,
 3;133,145,99;,
 3;40,52,8;,
 3;26,30,57;,
 3;27,30,26;,
 3;102,145,110;,
 3;91,79,28;,
 3;129,8,0;,
 3;57,30,156;,
 3;44,28,29;,
 3;36,94,37;,
 3;132,26,57;,
 3;15,38,2;,
 3;67,10,24;,
 3;54,29,55;,
 3;55,25,26;,
 3;55,29,25;,
 3;44,91,28;,
 3;38,62,2;,
 3;98,171,133;,
 3;57,156,6;,
 3;130,24,68;,
 3;2,1,20;,
 3;8,52,6;,
 3;67,130,172;,
 3;24,20,68;,
 3;25,11,13;,
 3;1,0,49;,
 3;68,17,157;,
 3;1,49,18;,
 3;6,156,14;,
 3;1,18,17;,
 3;93,109,79;;
 
 MeshMaterialList {
  1;
  296;
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0;;
  Material {
   0.400000;0.400000;0.400000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  173;
  -0.383616;0.412951;-0.826020;,
  -0.094027;0.386236;-0.917595;,
  -0.148918;0.088418;-0.984889;,
  0.548601;-0.649119;-0.526955;,
  0.474109;-0.604338;-0.640310;,
  0.592305;-0.693624;-0.409952;,
  -0.752266;0.641619;-0.149734;,
  -0.689573;0.575524;-0.439615;,
  -0.606513;0.597201;-0.524874;,
  0.193834;-0.466287;-0.863136;,
  0.449727;-0.395314;-0.800920;,
  -0.658574;0.619080;0.427809;,
  -0.756530;0.586220;0.289842;,
  -0.771232;0.633269;0.064583;,
  -0.829011;0.498064;-0.254310;,
  -0.140919;-0.193938;-0.970840;,
  0.191248;-0.261690;-0.946014;,
  0.197456;0.112267;-0.973862;,
  -0.056348;0.454949;-0.888733;,
  -0.055129;0.228089;-0.972078;,
  0.273265;-0.020829;-0.961713;,
  -0.658049;-0.218301;-0.720636;,
  -0.258382;-0.423959;-0.868043;,
  -0.504525;-0.387668;-0.771471;,
  0.500548;-0.303129;-0.810903;,
  -0.838271;0.481349;0.256133;,
  -0.822955;0.534156;-0.193449;,
  -0.735407;0.624918;-0.262021;,
  -0.705048;0.357788;0.612287;,
  -0.853425;0.277763;0.441037;,
  -0.786868;0.538651;-0.301154;,
  -0.864908;0.501874;0.007587;,
  -0.710988;0.259135;-0.653716;,
  -0.862224;0.245053;-0.443304;,
  -0.740178;0.078276;-0.667840;,
  0.199577;-0.675792;-0.709559;,
  0.679065;-0.668096;-0.304168;,
  0.656887;-0.675265;-0.335435;,
  -0.456356;0.013641;-0.889693;,
  -0.740158;-0.079268;-0.667745;,
  -0.789133;0.332427;-0.516489;,
  0.293954;-0.724381;-0.623590;,
  -0.010523;-0.643823;-0.765102;,
  -0.736748;0.335931;0.586816;,
  -0.648682;0.205039;0.732919;,
  0.622613;-0.324195;-0.712215;,
  0.680942;-0.522280;-0.513364;,
  -0.329769;-0.030216;0.943578;,
  -0.644756;0.325343;0.691695;,
  -0.256132;0.502643;-0.825679;,
  -0.431021;0.226312;-0.873501;,
  -0.400462;-0.089220;0.911960;,
  -0.833555;0.508822;-0.215141;,
  -0.848680;0.338145;-0.406694;,
  -0.835047;0.332732;0.438162;,
  -0.862966;0.498161;0.084417;,
  -0.786568;0.458854;0.413237;,
  -0.789734;0.561430;-0.247218;,
  0.144343;-0.556760;0.818037;,
  0.438400;-0.551276;0.709860;,
  0.283878;-0.741495;0.607946;,
  -0.689741;0.437973;0.576573;,
  -0.496598;0.240986;-0.833856;,
  0.662789;-0.642700;-0.384248;,
  -0.022201;-0.267548;0.963289;,
  -0.182266;-0.310947;0.932787;,
  0.614543;-0.614154;-0.495128;,
  0.619065;-0.500307;-0.605352;,
  0.423215;-0.113295;-0.898918;,
  -0.712097;0.303631;-0.633029;,
  -0.846313;0.439257;-0.301344;,
  -0.694209;0.545343;-0.469761;,
  -0.896292;0.146952;-0.418409;,
  0.267701;-0.355584;0.895487;,
  -0.027604;-0.272285;0.961821;,
  0.283181;-0.572832;0.769202;,
  -0.872791;0.485231;-0.052786;,
  -0.971475;0.222374;-0.082374;,
  -0.855169;0.472241;0.213717;,
  -0.568630;0.438700;0.695847;,
  -0.629443;0.558839;0.539908;,
  -0.622374;0.763656;-0.171699;,
  -0.726584;0.687077;0.001250;,
  0.707520;-0.700999;-0.089532;,
  0.621382;-0.751558;0.221462;,
  0.750414;-0.659878;0.037951;,
  -0.663706;0.463636;0.586972;,
  -0.623524;0.188456;0.758750;,
  -0.502132;0.372241;0.780577;,
  -0.440758;0.591333;0.675320;,
  -0.418234;0.359173;0.834311;,
  -0.576172;0.269535;0.771607;,
  -0.404178;0.096114;0.909617;,
  -0.451989;0.310124;0.836379;,
  0.680169;-0.695611;-0.231290;,
  0.694549;-0.640942;-0.326795;,
  -0.463894;0.781342;-0.417501;,
  -0.483090;0.470748;-0.738255;,
  0.527587;-0.538949;0.656648;,
  0.383873;-0.334495;0.860671;,
  -0.256600;0.137272;0.956720;,
  -0.144246;-0.062114;0.987590;,
  0.056179;-0.092072;0.994166;,
  -0.955771;0.225139;-0.189247;,
  -0.527585;0.069834;0.846627;,
  -0.263273;-0.164564;0.950582;,
  0.667053;-0.645390;-0.372172;,
  -0.365142;0.290917;0.884329;,
  -0.316059;0.130487;0.939723;,
  -0.524449;0.322681;0.787928;,
  -0.018695;0.063952;0.997778;,
  -0.221222;0.255339;0.941203;,
  -0.220437;0.237732;0.945987;,
  0.310161;-0.373413;-0.874279;,
  -0.433104;0.146123;0.889420;,
  -0.346440;0.158781;0.924537;,
  -0.280690;0.099512;0.954626;,
  0.237938;-0.089295;-0.967167;,
  -0.816373;0.238347;0.526047;,
  0.042535;-0.563451;0.825054;,
  -0.927699;0.250816;0.276526;,
  -0.323507;0.673690;-0.664443;,
  -0.526614;0.165035;-0.833932;,
  -0.386112;0.347176;-0.854626;,
  -0.296668;0.583475;-0.756006;,
  0.649490;-0.693455;0.311902;,
  0.454478;-0.726954;0.514769;,
  0.413928;-0.224807;-0.882114;,
  0.518189;-0.747770;0.415115;,
  -0.604557;0.422504;-0.675279;,
  0.606231;-0.372726;-0.702538;,
  -0.652036;0.173068;-0.738171;,
  -0.673101;0.544846;-0.500078;,
  0.545394;-0.425182;0.722333;,
  0.782933;-0.444236;-0.435511;,
  -0.423357;-0.092410;-0.901238;,
  -0.985746;0.132825;0.103258;,
  -0.340261;-0.416741;-0.842941;,
  -0.495684;0.860799;0.115420;,
  -0.915962;0.224967;0.332270;,
  0.335177;-0.480000;0.810714;,
  -0.463543;0.715238;0.523032;,
  -0.650807;0.688038;0.321020;,
  -0.733945;0.274785;0.621143;,
  -0.437164;0.840933;0.318934;,
  0.322923;-0.232066;0.917533;,
  -0.398291;0.910568;-0.110593;,
  -0.362681;0.926148;0.103499;,
  -0.353198;0.917539;-0.182684;,
  -0.367725;0.788421;0.493123;,
  -0.254730;0.685501;-0.682057;,
  -0.268782;0.770975;-0.577368;,
  -0.329437;0.851398;-0.408157;,
  -0.402549;0.859414;0.315218;,
  -0.410870;-0.349572;-0.842013;,
  -0.369570;0.039635;-0.928357;,
  -0.778584;0.611277;-0.141942;,
  0.404898;-0.253090;-0.878637;,
  0.734848;-0.459708;0.498665;,
  0.862982;-0.485459;-0.139972;,
  0.783410;-0.312932;-0.536975;,
  0.222771;-0.379970;-0.897773;,
  0.209749;-0.559871;-0.801592;,
  0.556088;-0.409976;0.722970;,
  0.640263;-0.507521;0.576615;,
  -0.013986;-0.020082;0.999700;,
  -0.851970;0.112099;-0.511450;,
  -0.390025;0.582170;-0.713413;,
  -0.701131;0.655648;-0.280249;,
  0.721528;-0.690656;-0.048906;,
  0.691994;-0.701160;0.171809;,
  0.654091;-0.592381;0.470372;,
  0.698156;-0.505401;-0.507097;;
  296;
  3;0,1,2;,
  3;3,4,5;,
  3;6,7,8;,
  3;4,9,10;,
  3;11,12,13;,
  3;14,7,6;,
  3;15,2,16;,
  3;17,18,19;,
  3;16,20,10;,
  3;21,22,23;,
  3;20,1,17;,
  3;15,16,9;,
  3;20,24,10;,
  3;25,13,26;,
  3;27,26,13;,
  3;28,25,29;,
  3;30,27,31;,
  3;11,25,28;,
  3;13,31,27;,
  3;32,33,34;,
  3;4,35,9;,
  3;3,36,37;,
  3;38,39,40;,
  3;35,41,42;,
  3;38,22,39;,
  3;29,43,44;,
  3;45,3,46;,
  3;47,44,48;,
  3;18,49,50;,
  3;51,44,47;,
  3;52,40,53;,
  3;54,55,56;,
  3;6,52,57;,
  3;52,53,57;,
  3;58,59,60;,
  3;61,43,56;,
  3;38,40,62;,
  3;37,63,46;,
  3;47,64,65;,
  3;66,67,36;,
  3;17,68,20;,
  3;69,70,71;,
  3;72,70,69;,
  3;73,74,75;,
  3;76,77,78;,
  3;79,11,28;,
  3;80,11,79;,
  3;81,70,82;,
  3;81,71,70;,
  3;83,84,85;,
  3;86,87,88;,
  3;89,88,90;,
  3;82,70,76;,
  3;91,92,93;,
  3;94,95,37;,
  3;96,97,71;,
  3;71,97,69;,
  3;73,98,99;,
  3;34,50,32;,
  3;100,101,102;,
  3;14,30,103;,
  3;104,92,91;,
  3;105,92,104;,
  3;104,51,105;,
  3;106,95,83;,
  3;107,108,109;,
  3;110,111,112;,
  3;45,113,3;,
  3;76,78,82;,
  3;114,115,90;,
  3;115,114,116;,
  3;17,19,117;,
  3;100,93,92;,
  3;93,79,91;,
  3;86,118,87;,
  3;74,65,119;,
  3;120,86,78;,
  3;96,121,97;,
  3;119,75,74;,
  3;69,122,34;,
  3;121,123,97;,
  3;124,123,121;,
  3;49,0,8;,
  3;120,118,86;,
  3;80,12,11;,
  3;97,122,69;,
  3;84,125,126;,
  3;45,127,113;,
  3;51,104,44;,
  3;69,34,72;,
  3;128,60,59;,
  3;87,114,88;,
  3;129,62,40;,
  3;24,130,67;,
  3;131,132,53;,
  3;99,98,133;,
  3;63,85,134;,
  3;122,123,135;,
  3;77,70,72;,
  3;92,101,100;,
  3;136,120,77;,
  3;50,135,137;,
  3;101,92,105;,
  3;73,99,102;,
  3;73,102,74;,
  3;82,138,81;,
  3;90,88,114;,
  3;93,112,107;,
  3;118,120,139;,
  3;77,120,78;,
  3;74,101,105;,
  3;75,126,98;,
  3;100,102,112;,
  3;110,112,102;,
  3;58,140,59;,
  3;86,141,142;,
  3;78,142,82;,
  3;114,108,116;,
  3;71,81,96;,
  3;105,65,74;,
  3;107,109,93;,
  3;143,87,118;,
  3;86,89,141;,
  3;86,88,89;,
  3;142,141,144;,
  3;77,76,70;,
  3;142,138,82;,
  3;85,84,128;,
  3;136,77,103;,
  3;83,125,84;,
  3;91,44,104;,
  3;60,126,75;,
  3;102,101,74;,
  3;93,100,112;,
  3;99,145,102;,
  3;146,81,138;,
  3;60,119,58;,
  3;96,81,146;,
  3;146,147,148;,
  3;142,144,138;,
  3;141,89,149;,
  3;150,121,151;,
  3;141,149,144;,
  3;96,146,148;,
  3;138,144,147;,
  3;96,148,152;,
  3;146,138,147;,
  3;144,153,147;,
  3;151,121,152;,
  3;121,96,152;,
  3;144,149,153;,
  3;109,108,114;,
  3;50,122,135;,
  3;137,135,154;,
  3;143,114,87;,
  3;103,77,72;,
  3;154,135,155;,
  3;50,34,122;,
  3;136,139,120;,
  3;33,72,34;,
  3;135,123,155;,
  3;122,97,123;,
  3;78,86,142;,
  3;124,121,150;,
  3;14,103,33;,
  3;112,111,107;,
  3;12,143,139;,
  3;19,50,137;,
  3;12,139,31;,
  3;31,136,103;,
  3;31,139,136;,
  3;33,103,72;,
  3;109,114,143;,
  3;111,108,107;,
  3;111,116,108;,
  3;143,118,139;,
  3;13,12,31;,
  3;30,14,156;,
  3;79,109,80;,
  3;49,8,50;,
  3;80,109,143;,
  3;8,7,50;,
  3;30,31,103;,
  3;17,117,157;,
  3;18,50,19;,
  3;7,14,33;,
  3;80,143,12;,
  3;7,33,32;,
  3;7,32,50;,
  3;158,159,85;,
  3;160,45,134;,
  3;113,161,162;,
  3;159,160,134;,
  3;113,162,3;,
  3;134,45,46;,
  3;161,42,162;,
  3;163,59,140;,
  3;159,134,85;,
  3;127,45,160;,
  3;127,161,113;,
  3;158,85,164;,
  3;163,158,164;,
  3;163,164,59;,
  3;162,41,3;,
  3;162,42,41;,
  3;85,128,164;,
  3;140,58,64;,
  3;64,47,165;,
  3;164,128,59;,
  3;42,22,35;,
  3;64,58,65;,
  3;42,23,22;,
  3;134,46,63;,
  3;41,4,3;,
  3;46,3,37;,
  3;128,84,126;,
  3;23,131,21;,
  3;128,126,60;,
  3;41,35,4;,
  3;58,119,65;,
  3;21,166,39;,
  3;85,63,83;,
  3;131,166,21;,
  3;47,65,51;,
  3;35,22,9;,
  3;21,39,22;,
  3;51,65,105;,
  3;83,63,106;,
  3;60,75,119;,
  3;131,167,132;,
  3;167,168,132;,
  3;48,43,61;,
  3;166,131,53;,
  3;48,44,43;,
  3;63,37,106;,
  3;126,125,98;,
  3;4,10,67;,
  3;56,55,168;,
  3;9,16,10;,
  3;83,169,170;,
  3;4,67,66;,
  3;168,55,132;,
  3;125,171,98;,
  3;53,132,57;,
  3;83,95,169;,
  3;106,37,95;,
  3;132,55,26;,
  3;125,170,171;,
  3;9,22,15;,
  3;5,36,3;,
  3;75,98,73;,
  3;22,38,15;,
  3;5,66,36;,
  3;166,53,40;,
  3;43,54,56;,
  3;5,4,66;,
  3;166,40,39;,
  3;83,170,125;,
  3;43,29,54;,
  3;2,62,0;,
  3;40,8,129;,
  3;16,2,20;,
  3;62,129,0;,
  3;36,67,172;,
  3;133,145,99;,
  3;40,52,8;,
  3;26,30,57;,
  3;27,30,26;,
  3;102,145,110;,
  3;91,79,28;,
  3;129,8,0;,
  3;57,30,156;,
  3;44,28,29;,
  3;36,94,37;,
  3;132,26,57;,
  3;15,38,2;,
  3;67,10,24;,
  3;54,29,55;,
  3;55,25,26;,
  3;55,29,25;,
  3;44,91,28;,
  3;38,62,2;,
  3;98,171,133;,
  3;57,156,6;,
  3;130,24,68;,
  3;2,1,20;,
  3;8,52,6;,
  3;67,130,172;,
  3;24,20,68;,
  3;25,11,13;,
  3;1,0,49;,
  3;68,17,157;,
  3;1,49,18;,
  3;6,156,14;,
  3;1,18,17;,
  3;93,109,79;;
 }
 MeshTextureCoords {
  173;
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;;
 }
}