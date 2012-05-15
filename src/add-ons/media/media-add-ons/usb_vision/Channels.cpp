/*
 * This file is a part of BeOS USBVision driver project.
 * Copyright (c) 2003 by Siarzuk Zharski <imker@gmx.li>
 *
 * This file may be used under the terms of the BSD License
 *
 */

/* TODO: Look for the following channel lists ...
Brazil Air
China Air
Europe Air
Europe Cable
France Air
France Cable
Great Britain Air
Great Britain Cable
FM Radio
UKW Radio
*/

struct Channel{
  const char *name; 
  float frequency; // in MHz  
};

Channel Channels_US_Air[] = {
  { "2",  55.25},  { "3",  61.25},  { "4",  67.25},  { "5",  77.25},  { "6",  83.25},
  { "7",  175.25}, { "8",  181.25}, { "9",  187.25}, { "10", 193.25}, { "11", 199.25},    
  { "12", 205.25}, { "13", 211.25}, { "14", 471.25}, { "15", 477.25}, { "16", 483.25},    
  { "17", 489.25}, { "18", 495.25}, { "19", 501.25}, { "20", 507.25}, { "21", 513.25},   
  { "22", 519.25}, { "23", 525.25}, { "24", 531.25}, { "25", 537.25}, { "26", 543.25},    
  { "27", 549.25}, { "28", 555.25}, { "29", 561.25}, { "30", 567.25}, { "31", 573.25},    
  { "32", 579.25}, { "33", 585.25}, { "34", 591.25}, { "35", 597.25}, { "36", 603.25},
  { "37", 609.25}, { "38", 615.25}, { "39", 621.25}, { "40", 627.25}, { "41", 633.25},
  { "42", 639.25}, { "43", 645.25}, { "44", 651.25}, { "45", 657.25}, { "46", 663.25},
  { "47", 669.25}, { "48", 675.25}, { "49", 681.25}, { "50", 687.25}, { "51", 693.25},
  { "52", 699.25}, { "53", 705.25}, { "54", 711.25}, { "55", 717.25}, { "56", 723.25},
  { "57", 729.25}, { "58", 735.25}, { "59", 741.25}, { "60", 747.25}, { "61", 753.25},
  { "62", 759.25}, { "63", 765.25}, { "64", 771.25}, { "65", 777.25}, { "66", 783.25},
  { "67", 789.25}, { "68", 795.25}, { "69", 801.25} };

Channel Channels_US_Cable[] = {
  { "4A", 73.25},    { "2",  55.25},    { "3",  61.25},    { "4",  67.25},    { "5",  77.25},    
  { "6",  83.25},    { "7",  175.25},   { "8",  181.25},   { "9",  187.25},   { "10", 193.25}, 
  { "11", 199.25},   { "12", 205.25},   { "13", 211.25},   { "A",  121.25},   { "B",  127.25},   
  { "C",  133.25},   { "D",  139.25},   { "E",  145.25},   { "F",  151.25},   { "G",  157.25},   
  { "H",  163.25},   { "I",  169.25},   { "J",  217.25},   { "K",  223.25},   { "L",  229.25},   
  { "M",  235.25},   { "N",  241.25},   { "O",  247.25},   { "P",  253.25},   { "Q",  259.25},   
  { "R",  265.25},   { "S",  271.25},   { "T",  277.25},   { "U",  283.25},   { "V",  289.25}, 
  { "W",  295.25},   { "W+1", 301.25},  { "W+2", 307.25},  { "W+3", 313.25},  { "W+4", 319.25},
  { "W+5", 325.25},  { "W+6", 331.25},  { "W+7", 337.25},  { "W+8", 343.25},  { "W+9", 349.25}, 
  { "W+10", 355.25}, { "W+11", 361.25}, { "W+12", 367.25}, { "W+13", 373.25}, { "W+14", 379.25}, 
  { "W+15", 385.25}, { "W+16", 391.25}, { "W+17", 397.25}, { "W+18", 403.25}, { "W+19", 409.25}, 
  { "W+20", 415.25}, { "W+21", 421.25}, { "W+22", 427.25}, { "W+23", 433.25}, { "W+24", 439.25}, 
  { "W+25", 445.25}, { "W+26", 451.25}, { "W+27", 457.25}, { "W+28", 463.25}, { "65",   469.25}, 
  { "66",   475.25}, { "67",   481.25}, { "68",   487.25}, { "69",   493.25}, { "70",   499.25}, 
  { "71",   505.25}, { "72",   511.25}, { "73",   517.25}, { "74",   523.25}, { "75",   529.25}, 
  { "76",   535.25}, { "77",   541.25}, { "78",   547.25}, { "79",   553.25}, { "80",   559.25}, 
  { "81",   565.25}, { "82",   571.25}, { "83",   577.25}, { "84",   583.25}, { "85",   589.25}, 
  { "86",   595.25}, { "87",   601.25}, { "88",   607.25}, { "89",   613.25}, { "90",   619.25}, 
  { "91",   625.25}, { "92",   631.25}, { "93",   637.25}, { "94",   643.25}, { "A�5",  91.25 }, 
  { "A�4",  97.25 }, { "A�3",  103.25}, { "A�2",  109.25}, { "A-1",  115.25}, { "100",  649.25}, 
  { "101",  655.25}, { "102",  661.25}, { "103",  667.25}, { "104",  673.25}, { "105",  679.25}, 
  { "106",  685.25}, { "107",  691.25}, { "108",  697.25}, { "109",  703.25}, { "110",  709.25},  
  { "111",  715.25}, { "112",  721.25}, { "113",  727.25}, { "114",  733.25}, { "115",  739.25},  
  { "116",  745.25}, { "117",  751.25}, { "118",  757.25}, { "119",  763.25}, { "120",  769.25},  
  { "121",  775.25}, { "122",  781.25}, { "123",  787.25}, { "124",  793.25}, { "125",  799.25} };

Channel Channels_US_Cable_HRC[] = {
  { "2",  54.00},    { "3",  60.00},    { "4",  66.00},    { "5",  76.00},    
  { "6",  82.00},    { "7",  174.00},   { "8",  180.00},   { "9",  186.00},   { "10", 192.00}, 
  { "11", 198.00},   { "12", 204.00},   { "13", 210.00},   { "A",  120.00},   { "B",  126.00},   
  { "C",  132.00},   { "D",  138.00},   { "E",  144.00},   { "F",  150.00},   { "G",  156.00},   
  { "H",  162.00},   { "I",  168.00},   { "J",  216.00},   { "K",  222.00},   { "L",  228.00},   
  { "M",  234.00},   { "N",  240.00},   { "O",  246.00},   { "P",  252.00},   { "Q",  258.00},   
  { "R",  264.00},   { "S",  270.00},   { "T",  276.00},   { "U",  282.00},   { "V",  288.00}, 
  { "W",  294.00},   { "W+1", 300.00},  { "W+2", 306.00},  { "W+3", 312.00},  { "W+4", 318.00},
  { "W+5", 324.00},  { "W+6", 330.00},  { "W+7", 336.00},  { "W+8", 342.00},  { "W+9", 348.00}, 
  { "W+10", 354.00}, { "W+11", 360.00}, { "W+12", 366.00}, { "W+13", 372.00}, { "W+14", 378.00}, 
  { "W+15", 384.00}, { "W+16", 390.00}, { "W+17", 396.00}, { "W+18", 402.00}, { "W+19", 408.00}, 
  { "W+20", 414.00}, { "W+21", 420.00}, { "W+22", 426.00}, { "W+23", 432.00}, { "W+24", 438.00}, 
  { "W+25", 444.00}, { "W+26", 450.00}, { "W+27", 456.00}, { "W+28", 462.00}, { "65",   468.00}, 
  { "66",   474.00}, { "67",   480.00}, { "68",   486.00}, { "69",   492.00}, { "70",   498.00}, 
  { "71",   504.00}, { "72",   510.00}, { "73",   516.00}, { "74",   522.00}, { "75",   528.00}, 
  { "76",   534.00}, { "77",   540.00}, { "78",   546.00}, { "79",   552.00}, { "80",   558.00}, 
  { "81",   564.00}, { "82",   570.00}, { "83",   576.00}, { "84",   582.00}, { "85",   588.00}, 
  { "86",   594.00}, { "87",   600.00}, { "88",   606.00}, { "89",   612.00}, { "90",   618.00}, 
  { "91",   624.00}, { "92",   630.00}, { "93",   636.00}, { "94",   642.00}, { "A�5",  90.00 }, 
  { "A�4",  96.00 }, { "A�3",  102.00}, { "A�2",  108.00}, { "A-1",  114.00}, { "100",  648.00}, 
  { "101",  654.00}, { "102",  660.00}, { "103",  666.00}, { "104",  672.00}, { "105",  678.00}, 
  { "106",  684.00}, { "107",  690.00}, { "108",  696.00}, { "109",  702.00}, { "110",  708.00},  
  { "111",  714.00}, { "112",  720.00}, { "113",  726.00}, { "114",  732.00}, { "115",  738.00},  
  { "116",  744.00}, { "117",  750.00}, { "118",  756.00}, { "119",  762.00}, { "120",  768.00},  
  { "121",  774.00}, { "122",  780.00}, { "123",  786.00}, { "124",  792.00}, { "125",  798.00} };

Channel Japan_Air[]={
  { "1",  91.25},  { "2",  97.25},  { "3",  103.25}, { "4",  171.25}, { "5",  177.25},   
  { "6",  183.25}, { "7",  189.25}, { "8",  193.25}, { "9",  199.25}, { "10", 205.25},   
  { "11", 211.25}, { "12", 217.25}, { "13", 471.25}, { "14", 477.25}, { "15", 483.25},   
  { "16", 489.25}, { "17", 495.25}, { "18", 501.25}, { "19", 507.25}, { "20", 513.25},   
  { "21", 519.25}, { "22", 525.25}, { "23", 531.25}, { "24", 537.25}, { "25", 543.25},   
  { "26", 549.25}, { "27", 555.25}, { "28", 561.25}, { "29", 567.25}, { "30", 573.25},   
  { "31", 579.25}, { "32", 585.25}, { "33", 591.25}, { "34", 597.25}, { "35", 603.25},   
  { "36", 609.25}, { "37", 615.25}, { "38", 621.25}, { "39", 627.25}, { "40", 633.25},   
  { "41", 639.25}, { "42", 645.25}, { "43", 651.25}, { "44", 657.25}, { "45", 663.25},  
  { "46", 669.25}, { "47", 675.25}, { "48", 681.25}, { "49", 687.25}, { "50", 693.25},  
  { "51", 699.25}, { "52", 705.25}, { "53", 711.25}, { "54", 717.25}, { "55", 723.25},  
  { "56", 729.25}, { "57", 735.25}, { "58", 741.25}, { "59", 747.25}, { "60", 753.25},  
  { "61", 759.25}, { "62", 765.25} };

Channel Japan_Cable[]={
  { "1",   91.25},  { "2",   97.25},  { "3",   103.25}, { "4",   171.25}, { "5",   177.25},  
  { "6",   183.25}, { "7",   189.25}, { "8",   193.25}, { "9",   199.25}, { "10",  205.25},  
  { "11",  211.25}, { "12",  217.25}, { "C13", 109.25}, { "C14", 115.25}, { "C15", 121.25},  
  { "C16", 127.25}, { "C17", 133.25}, { "C18", 139.25}, { "C19", 145.25}, { "C20", 151.25},  
  { "C21", 157.25}, { "C22", 165.25}, { "C23", 223.25}, { "C24", 229.25}, { "C25", 235.25},  
  { "C26", 241.25}, { "C27", 247.25}, { "C28", 253.25}, { "C29", 259.25}, { "C30", 265.25},  
  { "C31", 271.25}, { "C32", 277.25}, { "C33", 293.25}, { "C34", 289.25}, { "C35", 295.25},  
  { "C36", 301.25}, { "C37", 307.25}, { "C38", 313.25}, { "C39", 319.25}, { "C40", 325.25},  
  { "C41", 331.25}, { "C42", 337.25}, { "C43", 343.25}, { "C44", 349.25}, { "C45", 355.25},  
  { "C46", 361.25}, { "C47", 367.25}, { "C48", 373.25}, { "C49", 379.25}, { "C50", 385.25}, 
  { "C51", 391.25}, { "C52", 397.25}, { "C53", 403.25}, { "C54", 409.25}, { "C55", 415.25}, 
  { "C56", 421.25}, { "C57", 427.25}, { "C58", 433.25}, { "C59", 439.25}, { "C60", 445.25}, 
  { "C61", 451.25}, { "C62", 457.25}, { "C63", 463.25} };

International_Air
{
      E2  48.25  
      E3  55.25  
      E4  62.25  
      E5  175.25 
      E6  182.25 
      E7  189.25 
      E8  196.25 
      E9  203.25 
      E10 210.25 
      E11 217.25 
      E12 224.25 
      IA  53.75  
      IB  62.25  
      IC  82.25  
      ID  175.25 
      IE  183.25 
      IF  192.75 
      IG  201.25 
      IH  210.25 
      21  471.25 
      22  479.25 
      23  487.25 
      24  495.25 
      25  503.25 
      26  511.25 
      27  519.25 
      28  527.25 
      29  535.25 

  30  543.25  C30 
  31  551.25  C31 
  32  559.25  C32 
  33  567.25  C33 
  34  575.25  C34 
  35  583.25  C35 
  36  591.25  C36 
  37  599.25  C37 
  38  607.25  C38 
  39  615.25  C39 
  40  623.25  C40 
  41  631.25  C41 
  42  639.25  C42 
  43  647.25  C43 
  44  655.25  C44 
  45  663.25  C45 
  46  671.25  C46 
  47  679.25  C47 
  48  687.25  C48 
  49  695.25  C49 
  50  703.25  C50 
  51  711.25  C51 
  52  719.25  C52 
  53  727.25  C53 
  54  735.25  C54 
  55  743.25  C55 
  56  751.25  C56 
  57  759.25  C57 
  58  767.25  C58 
  59  775.25  C59 
  60  783.25  C60 
  61  791.25  C61 
  62  799.25  C62 
  63  807.25  C63 
  64  815.25  C64 
  65  823.25  C65 
  66  831.25  C66 
  67  839.25  C67 
  68  847.25  C68 
  69  855.25  C69 
  E2A 49.75   C70 
  AS1 57.25   C71 
  AS2 64.25   C72 
  AS3 86.25   C73 
  AS4 95.25   C74 
  AS5 102.25  C75 
  AS5A    138.25  
  AS10    209.25  
  AS11    216.25  
  IH1     217.25  
  IND2    55.25   
  IND3    62.25   
  IND4    175.25  
  IND5    182.25  
  IND6    189.25  
  IND7    196.25  
  IND8    203.25  
  IND9    210.25  
  IND10   217.25  
  IND11   224.25  

};

International_Cable
{
 Channel  Freq    
      E2  48.25   
      E3  55.25   
      E4  62.25   
      S01 69.25   
      S02 76.25   
      S03 83.25   
      S1  105.25  

   S2  112.25 
   S3  119.25 
   S4  126.25 
   S5  133.25 
   S6  140.25 
   S7  147.25 
   S8  154.25 
   S9  161.25 
   S10 168.25 
   E5  175.25 
   E6  182.25 
   E7  189.25 
   E8  196.25 
   E9  203.25 
   E10 210.25 
   E11 217.25 
   E12 224.25 
   S11 231.25 
   S12 238.25 
   S13 245.25 
   S14 252.25 
   S15 259.25 
   S16 266.25 
   S17 273.25 
   S18 280.25 
   S19 287.25 
   S20 294.25 
   S21 303.25 
   S22 311.25 
   S23 319.25 
   S24 327.25 
   S25 335.25 
   S26 343.25 
   S27 351.25 
   S28 359.25 
   S29 367.25 
   S30 375.25 
   S31 383.25 
   S32 391.25 
   S33 399.25 
   S34 407.25 
   S35 415.25 
   S36 423.25 
   S37 431.25 
   S38 439.25 
   S39 447.25 
   S40 455.25 
   S41 463.25 
};

Channel UK_Air[] = {
  { "A",   45.75},  { "B",   53.75},  { "C",   61.75},  { "D",   175.25}, { "E",   183.25},  
  { "F",   191.25}, { "G",   199.25}, { "H",   207.25}, { "J",   215.25}, { "C10", 223.25},  
  { "C11", 231.25}, { "C13", 247.25}, { "B21", 471.25}, { "B22", 479.25}, { "B23", 487.25}, 
  { "B24", 495.25}, { "B25", 503.25}, { "B26", 511.25}, { "B27", 519.25}, { "B28", 527.25},
  { "B29", 535.25}, { "B30", 543.25}, { "B31", 551.25}, { "B32", 559.25}, { "B33", 567.25}, 
  { "B34", 575.25}, { "B35", 583.25}, { "B36", 591.25}, { "B37", 599.25}, { "B38", 607.25}, 
  { "B39", 615.25}, { "B40", 623.25}, { "B41", 631.25}, { "B42", 639.25}, { "B43", 647.25}, 
  { "B44", 655.25}, { "B45", 663.25}, { "B46", 671.25}, { "B47", 679.25}, { "B48", 687.25}, 
  { "B49", 695.25}, { "B50", 703.25}, { "B51", 711.25}, { "B52", 719.25}, { "B53", 727.25}, 
  { "B54", 735.25}, { "B55", 743.25}, { "B56", 751.25}, { "B57", 759.25}, { "B58", 767.25}, 
  { "B59", 775.25}, { "B60", 783.25}, { "B61", 791.25}, { "B62", 799.25}, { "B63", 807.25}, 
  { "B64", 815.25}, { "B65", 823.25}, { "B66", 831.25}, { "B67", 839.25}, { "B68", 847.25},
  { "B69", 855.25}, { "B1",  45.00 }, { "B2",  51.75 }, { "B3",  56.75 }, { "B4",  61.75 }, 
  { "B5",  66.75 }, { "B6",  179.75}, { "B7",  184.75}, { "B8",  189.75}, { "B9",  194.75}, 
  { "B10", 199.75}, { "B11", 204.75}, { "B12", 209.75}, { "B13", 214.75}, { "B14", 219.75} };

UK_Cable
{
 Channel  Freq   
      A1  47.25  
      A2  55.25  

  A3  63.25  
  A4  71.25  
  A5  79.25  
  A6  87.25  
  A7  95.25  
  A8  103.25 
  A9  111.25 
  A10 119.25 
  A11 127.25 
  A12 135.25 
  A13 143.25 
  A14 151.25 
  A15 159.25 
  A16 167.25 
  A17 175.25 
  A18 183.25 
  A19 191.25 
  A20 199.25 
  A21 207.25 
  A22 215.25 
  A23 223.25 
  A24 231.25 
  A25 239.25 
  A26 247.25 
  A27 255.25 
  A28 263.25 
  A29 271.25 
  A30 279.25 
  A31 287.25 
  A32 295.25 
  E2  48.25  
  E3  55.25  
  E4  62.25  
  S01 69.25  
  S02 76.25  
  S03 83.25  
  S1  105.25 
  S2  112.25 
  S3  119.25 
  S4  126.25 
  S5  133.25 
  S6  140.25 
  S7  147.25 
  S8  154.25 
  S9  161.25 
  S10 168.25 
  E5  175.25 
  E6  182.25 
  E7  189.25 
  E8  196.25 
  E9  203.25 
  E10 210.25 
  E11 217.25 
  E12 224.25 
  S11 231.25 
  S12 238.25 
  S13 245.25 
  S14 252.25 
  S15 259.25 
  S16 266.25 
  S17 273.25 
  S18 280.25 
  S19 287.25 
  S20 294.25 
  S21 303.25 
  S22 311.25 
  S23 319.25 
  S24 327.25 
  S25 335.25 
  S26 343.25 
  S27 351.25 
  S28 359.25 

   S29 367.25  
   S30 375.25  
   S31 383.25  
   S32 391.25  
   S33 399.25  
   S34 407.25  
   S35 415.25  
   S36 423.25  
   S37 431.25  
   S38 439.25  
   S39 447.25  
   S40 455.25  
   S41 463.25  

};

French_Air
{
 Channel  Freq    
      FA  47.75   
      L2  49.25   
      L3  54.00   
      FB  55.75   
      L4  57.25   
      FC1 60.50   
      FC  63.75   
      F1  176.00  
      F2  184.00  
      F3  192.00  
      F4  200.00  
      F5  208.00  
      F6  216.00  
      B21 471.25  
      B22 479.25  
      B23 487.25  
      B24 495.25  
      B25 503.25  
      B26 511.25  
      B27 519.25  
      B28 527.25  
      B29 535.25  
      B30 543.25  
      B31 551.25  
      B32 559.25  
      B33 567.25  
      B34 575.25  
      B35 583.25  
      B36 591.25  
      B37 599.25  
      B38 607.25  
      B39 615.25  
      B40 623.25  
      B41 631.25  
      B42 639.25  
      B43 647.25  
      B44 655.25  
      B45 663.25  
      B46 671.25  
      B47 679.25  
      B48 687.25  
      B49 695.25  
      B50 703.25  
      B51 711.25  
      B52 719.25  


   B53 727.25  
   B54 735.25  
   B55 743.25  
   B56 751.25  
   B57 759.25  
   B58 767.25  
   B59 775.25  
   B60 783.25  
   B61 791.25  
   B62 799.25  
   B63 807.25  
   B64 815.25  
   B65 823.25  
   B66 831.25  
   B67 839.25  
   B68 847.25  
   B69 855.25  

};

French_Cable
{
  Channel  Freq   
       E2  48.25  
       E3  55.25  
       E4  62.25  
       S01 69.25  
       S02 76.25  
       S03 83.25  
       S1  105.25 
       S2  112.25 
       S3  119.25 
       S4  126.25 
       S5  133.25 
       S6  140.25 
       S7  147.25 
       S8  154.25 
       S9  161.25 
       S10 168.25 
       E5  175.25 
       E6  182.25 
       E7  189.25 
       E8  196.25 
       E9  203.25 
       E10 210.25 
       E11 217.25 
       E12 224.25 
       S11 231.25 
       S12 238.25 
       S13 245.25 
       S14 252.25 
       S15 259.25 
       S16 266.25 
       S17 273.25 
       S18 280.25 
       S19 287.25 
       S20 294.25 
       S21 303.25 
       S22 311.25 
       S23 319.25 
       S24 327.25 
       S25 335.25 
       S26 343.25 
       S27 351.25 
       S28 359.25 
       S29 367.25 
       S30 375.25 
       S31 383.25 
       S32 391.25 
       S33 399.25 
       S34 407.25 
       S35 415.25 
       S36 423.25 

 S37 431.25 
 S38 439.25 
 S39 447.25 
 S40 455.25 
 S41 463.25 

};

Channel Channels_FMRadio[] = {
/*???*/
};

Channel Channels_UKW_Radio[] = {
/*???*/
};

Channel Channels_xUSSR_Air[] = {
  {"1", 49.75},   {"2", 59.25},   {"3", 77.25},   {"4", 85.25},   {"5", 93.25},
  {"6", 175.25},  {"7", 183.25},  {"8", 191.25},  {"9", 199.25},  {"10", 207.25},
  {"11", 215.25}, {"12", 223.25},
  {"21", 471.25}, {"22", 479.25}, {"23", 487.25}, {"24", 495.25}, {"25", 503.25},
  {"26", 511.25}, {"27", 519.25}, {"28", 527.25}, {"29", 535.25}, {"30", 543.25},
  {"31", 551.25}, {"32", 559.25}, {"33", 567.25}, {"34", 575.25}, {"35", 583.25},
  {"36", 591.25}, {"37", 599.25}, {"38", 607.25}, {"39", 615.25}, {"40", 623.25},
  {"41", 631.25}, {"42", 639.25}, {"43", 647.25}, {"44", 655.25}, {"45", 663.25},
  {"46", 671.25}, {"47", 679.25}, {"48", 687.25}, {"49", 695.25}, {"50", 703.25},
  {"51", 711.25}, {"52", 719.25}, {"53", 727.25}, {"54", 735.25}, {"55", 743.25},
  {"56", 751.25}, {"57", 759.25}, {"58", 767.25}, {"59", 775.25}, {"60", 783.25},
  {"61", 791.25}, {"62", 799.25}, {"63", 807.25}, {"64", 815.25}, {"65", 823.25},
  {"66", 831.25}, {"67", 839.25}, {"68", 847.25}, {"69", 855.25}};

Channel Channels_xUSSR_Cable[] = {
  {"70", 111.25},  {"71", 119.25},  {"72", 127.25},  {"73", 135.25},  {"74", 143.25},
  {"75", 141.25},  {"76", 159.25},  {"77", 167.25},  {"78", 231.25},  {"79", 239.25},
  {"80", 247.25},  {"81", 255.25},  {"82", 263.25},  {"83", 271.25},  {"84", 279.25},
  {"85", 287.25},  {"86", 295.25},  {"87", 303.25},  {"88", 311.25},  {"89", 319.25},
  {"90", 327.25},  {"91", 335.25},  {"92", 343.25},  {"93", 351.25},  {"94", 359.25},
  {"95", 367.25},  {"96", 375.25},  {"97", 383.25},  {"98", 391.25},  {"99", 399.25},
  {"100", 407.25}, {"101", 415.25}, {"102", 423.25}, {"103", 431.25}, {"104", 439.25},
  {"105", 447.25}, {"106", 455.25}, {"107", 463.25} };

Channel Channels_EuropeAir[] = {
  {"", }, {"", }, {"", }, {"", },  {"", },  {"", },
};

Channel Channels_EuropeCable[] = {
  {"", }, {"", }, {"", }, {"", },  {"", },  {"", },
};

Channel Channels_AustraliaAir[] = {
  { "0", 46.25},   { "1", 57.25},   { "2", 64.25},   { "3", 86.25},   { "4", 95.25}, 
  { "5", 102.25},  { "5A", 138.25}, { "6", 175.25},  { "7", 182.25},  { "8", 189.25}, 
  { "9", 196.25},  { "10", 209.25}, { "11", 216.25}, { "28", 527.25}, { "29", 534.25}, 
  { "30", 541.25}, { "31", 548.25}, { "32", 555.25}, { "33", 562.25}, { "34", 569.25}, 
  { "35", 576.25}, { "39", 604.25}, { "40", 611.25}, { "41", 618.25}, { "42", 625.25}, 
  { "43", 632.25}, { "44", 639.25}, { "45", 646.25}, { "46", 653.25}, { "47", 660.25}, 
  { "48", 667.25}, { "49", 674.25}, { "50", 681.25}, { "51", 688.25}, { "52", 695.25}, 
  { "53", 702.25}, { "54", 709.25}, { "55", 716.25}, { "56", 723.25}, { "57", 730.25}, 
  { "58", 737.25}, { "59", 744.25}, { "60", 751.25}, { "61", 758.25}, { "62", 765.25}, 
  { "63", 772.25}, { "64", 779.25}, { "65", 786.25}, { "66", 793.25}, { "67", 800.25}, 
  { "68", 807.25}, { "69", 814.25} };

Channel Channels_IrelandAir[] = {
  
};
