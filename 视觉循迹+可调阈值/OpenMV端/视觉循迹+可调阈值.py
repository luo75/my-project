# Untitled - By: lyh_5 - 周二 1月 23 2024
#浅浅练习一下

#功能：模拟循迹模块，并将循迹结果传给stm32
#     菜单调阈值
#     自动调阈值
import sensor, image, time
import display
from pyb import UART

uart = UART(3, 115200, timeout_char=1000)                         # 使用给定波特率初始化
uart.init(115200, bits=8, parity=None, stop=1, timeout_char=1000) # 使用给定参数初始化

sensor.reset()
sensor.set_pixformat(sensor.RGB565)
sensor.set_framesize(sensor.QQVGA2) #128*160
sensor.skip_frames(time = 2000)
sensor.set_auto_gain(False) # must be turned off for color tracking
sensor.set_auto_whitebal(False) # must be turned off for color tracking
#clock = time.clock()
lcd = display.SPIDisplay()

areas=([40,70,25,25],[65,70,25,25],[90,70,25,25])
red=[31, 36, 46, 60, 20, 55]  #红线阈值

#阈值使能标识符
the_enable=0
#串口命令标志位
command=0

#入口参数：图片
#输出：循迹的列表，识别符合red的阈值，就定为1.否则为0
def Track(img):     #循迹函数
    track=[0,0,0]
    for area in areas:
        static=img.statistics(roi=area)
        if red[0]<static.l_mean()<red[1] and red[2]<static.a_mean()<red[3] and red[4]<static.b_mean()<red[5]:
            track[areas.index(area)]=1
    return track

def Show(Track):   #显示循迹的结果函数
    for area in areas:
        img.draw_rectangle(area)
        if Track[areas.index(area)]==1:
            img.draw_string(area[0],area[1],"1",scale=3)
        else:
            img.draw_string(area[0],area[1],"0",scale=3)


def Sending(Track):     #将数据包传给stm32(其实发送单个数据不需要用数据包，多此一举仅作为练习)
    Track_D=Track[0]*1+Track[1]*2+Track[2]*4    #将循迹数据转为十进制
    data=bytearray([0xa3,0xb3,Track_D,0xc3]) #帧头 + 帧头 +循迹结果+ 帧尾
    uart.write(data)

def Auto_SetThr():
    global command
    global red

    for i in range(200):
        img = sensor.snapshot()
        img.draw_rectangle((75,55,10,10), color=(255,0,0))  #圈出搜寻区域
        lcd.write(img)
        Statistics = img.get_statistics(roi=(75,55,10,10))  #得到搜寻区域内的图像统计信息
        red = [Statistics.l_min(),Statistics.l_max(), #从统计信息中得到色块阈值
                     Statistics.a_min(),Statistics.a_max(),
                     Statistics.b_min(),Statistics.b_max()]
    command=0
def manual_setThr():  #手动调阈值
    global command
    if(command==99): red[0]+=1
    if(command==100): red[1]+=1
    if(command==101): red[2]+=1
    if(command==102): red[3]+=1
    if(command==103): red[4]+=1
    if(command==104): red[5]+=1
    if(command==105): red[0]-=1
    if(command==106): red[1]-=1
    if(command==107): red[2]-=1
    if(command==108): red[3]-=1
    if(command==109): red[4]-=1
    if(command==110): red[5]-=1

    command=0
    thr=bytearray([0xa3,0xb3,red[0],red[1],red[2],
                   red[3],red[4],red[5],0xc3])

    uart.write(thr)

    img.binary([red]) #将图像转换成lab二值化图像

while(True):
    img = sensor.snapshot()
    if uart.any(): #如果接收到
        command=uart.readchar() #readchar读取字节的ASCII码,返回的是一个int类型

    if(command==111): Auto_SetThr() #如果接收命令‘0’，则进入自动调阈值

    if(command==97): the_enable=1  #如果接收命令‘a’，则进入手动调整阈值
    if(command==98): the_enable=0

    if the_enable:
        manual_setThr()

    if the_enable!=1:
        Track_Result=Track(img)
        #print(Track_Result)
        Show(Track_Result)
        Sending(Track_Result)

    lcd.write(img)
    print(red)


