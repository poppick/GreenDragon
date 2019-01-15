#coding:utf8

month = 11
year = 2016
xianjin = 18
fangdai = 120
p8_xianjin = xianjin
p4_xianjin = xianjin
qiankuan = 44
waijie = 4
daikuan = 120
fangjia = 350

#房贷情况
yuegong = 7664
yuegong_lixi = 1781


def calc_fangdai(year, month):
    month_count = (year - 2016) * 12 + (month - 5)
    yuegong_benjin = yuegong - yuegong_lixi
    yihuan = float(month_count *  yuegong_benjin) / 10000

    fangdai = daikuan - yihuan
    return fangdai

def calc_guding(year, month):
    guding = fangjia - calc_fangdai(year, month)
    return guding

def calc_total(year, month):
    total = calc_guding(year, month) - qiankuan + waijie + xianjin
    return total 


def huanfang(year, month):
    global yuegong, yuegong_lixi, daikuan, xianjin
    new_daikuan = 350 * 0.95 * 0.7 #= 232.75
    xianjin_shouru = new_daikuan - calc_fangdai(year, month)
    chengben = 8.25

    daikuan = new_daikuan
    yuegong = 11297
    yuegong_lixi = 4853
    xianjin += xianjin_shouru - chengben


def calc_lixi(benjin, rate):
    lixi = float(benjin * rate) / 12;
    return lixi

def benjin_increase(yearm, month):
    global xianjin
    if month == 1:
        xianjin += 6
    if year == 2018 and month == 5:
        huanfang(year, month)
        pass
    xianjin += 2
	
if __name__ == "__main__":

    calc_year = 10 
    print "现在是%d年%d月, 总资产: %.3f万元, 其中房贷%.3f万, 负债%.3f万, 固定%.3f万, 现金%.3f万" %(
            year, month, calc_total(year, month), calc_fangdai(year, month), qiankuan, calc_guding(year, month), xianjin)
    print "计算 %d 年后的财务情况" % calc_year

    for y in range(calc_year):
        year +=  1
        for m in range(12):
            month =  (month) % 12 + 1
            
            lixi = calc_lixi(xianjin, 0.08)
            xianjin = xianjin + lixi
            benjin_increase(year, month)
            
            print "%d年 %d月 总资产=%.3f, 其中房贷%.3f万, 负债%.3f万, 固定%.3f万, 现金%.3f万, 当月理财收入%.3f" %(
                    year, month, calc_total(year, month), calc_fangdai(year, month), qiankuan, calc_guding(year, month), xianjin, lixi)
