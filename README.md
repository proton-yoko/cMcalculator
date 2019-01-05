cMcalculator
====

Overview

make a personal vcf file (pformat txt) from 1000 genome project vcf file

calculate the shared cM of 2 pformat txtfile


## memo

$ cat xxx/ALL.chr22.integrated_phase1_v3.20101123.snps_indels_svs.genotypes.vcf | awk ’{print $1, $2, $3, $4, $5, $6, $220}’| head -10

これで1000genome projectの特定の行から新しいtxtファイルを作成

$ g++ vcftxt2pformat.cpp -o vcftxt2pformat

$ vcftxt2pformat HG00524_chr22.txt >> HG00524_chr22_pformat.txt

これでvcfファイルから抽出したある個人のデータをpformatに変換

pformat

chr_num pos 遺伝子名　ref alt 0|0 左の塩基　右の塩基　0+0


## Author

[proton] (https://github.com/proton-yoko/)
