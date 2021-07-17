#include "EasyX.h"

void EasyX::initialize() {
    setbkcolor(BKCOLOR);
    cleardevice();
    LOGFONT f;
    RECT r;

    //����������
    setlinecolor(BLACK);
    setlinestyle(PS_SOLID, 1);
    for (int i = 75; i <= 675; i += 50) {
        line(i, 25, i, 725);
        line(25, i, 725, i);
    }
    setlinestyle(PS_SOLID, 3);
    line(25, 25, 25, 725);
    line(725, 25, 725, 725);
    line(25, 25, 725, 25);
    line(25, 725, 725, 725);

    //�������̵�
    setfillcolor(BLACK);
    solidcircle(375, 375, 3);
    solidcircle(175, 175, 3);
    solidcircle(175, 575, 3);
    solidcircle(575, 175, 3);
    solidcircle(575, 575, 3);

    //����������ʾ����
    gettextstyle(&f);
    f.lfHeight = 30;
    f.lfQuality = ANTIALIASED_QUALITY;
    _tcscpy_s(f.lfFaceName, _T("΢���ź�"));
    settextstyle(&f);
    settextcolor(myBLACK);
    setbkcolor(BKCOLOR);
    outtextxy(760, 20, _T("����-����:"));

    //��������ѡ��1
    setfillcolor(myBLACK);
    solidroundrect(760, 60, 930, 120, 25, 25);
    gettextstyle(&f);
    f.lfHeight = 35;
    f.lfQuality = ANTIALIASED_QUALITY;
    _tcscpy_s(f.lfFaceName, _T("΢���ź�"));
    settextstyle(&f);
    settextcolor(myWHITE);
    setbkcolor(myBLACK);
    r = {760, 60, 930, 120};
    drawtext(_T("��  ��"), &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

    //��������ѡ��2
    setfillcolor(myWHITE);
    solidroundrect(760, 130, 930, 190, 25, 25);
    setlinecolor(myBLACK);
    setlinestyle(PS_SOLID, 3);
    setbkcolor(myWHITE);
    roundrect(761, 131, 929, 189, 25, 25);
    gettextstyle(&f);
    f.lfHeight = 35;
    f.lfQuality = ANTIALIASED_QUALITY;
    _tcscpy_s(f.lfFaceName, _T("΢���ź�"));
    settextstyle(&f);
    settextcolor(myBLACK);
    setbkcolor(myWHITE);
    r = {760, 130, 930, 190};
    drawtext(_T("A    I"), &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

    //���ƺ�����ʾ����
    gettextstyle(&f);
    f.lfHeight = 30;
    f.lfQuality = ANTIALIASED_QUALITY;
    _tcscpy_s(f.lfFaceName, _T("΢���ź�"));
    settextstyle(&f);
    settextcolor(myBLACK);
    setbkcolor(BKCOLOR);
    outtextxy(760, 210, _T("����-����:"));

    //���ƺ���ѡ��1
    setfillcolor(myBLACK);
    solidroundrect(760, 250, 930, 310, 25, 25);
    gettextstyle(&f);
    f.lfHeight = 35;
    f.lfQuality = ANTIALIASED_QUALITY;
    _tcscpy_s(f.lfFaceName, _T("΢���ź�"));
    settextstyle(&f);
    settextcolor(myWHITE);
    setbkcolor(myBLACK);
    r = {760, 250, 930, 310};
    drawtext(_T("��  ��"), &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

    //���ƺ���ѡ��2
    setfillcolor(myWHITE);
    solidroundrect(760, 320, 930, 380, 25, 25);
    setlinecolor(myBLACK);
    setlinestyle(PS_SOLID, 3);
    setbkcolor(myWHITE);
    roundrect(761, 321, 929, 379, 25, 25);
    gettextstyle(&f);
    f.lfHeight = 35;
    f.lfQuality = ANTIALIASED_QUALITY;
    _tcscpy_s(f.lfFaceName, _T("΢���ź�"));
    settextstyle(&f);
    settextcolor(myBLACK);
    setbkcolor(myWHITE);
    r = {760, 320, 930, 380};
    drawtext(_T("A    I"), &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

    //���ƿ�ʼ��ť
    setfillcolor(myWHITE);
    solidroundrect(760, 420, 930, 480, 25, 25);
    setlinecolor(myBLACK);
    setlinestyle(PS_SOLID, 3);
    setbkcolor(myWHITE);
    roundrect(761, 421, 929, 479, 24, 24);
    roundrect(767, 427, 923, 473, 18, 18);
    gettextstyle(&f);
    f.lfHeight = 35;
    f.lfQuality = ANTIALIASED_QUALITY;
    _tcscpy_s(f.lfFaceName, _T("΢���ź�"));
    settextstyle(&f);
    settextcolor(myBLACK);
    setbkcolor(myWHITE);
    r = {760, 420, 930, 480};
    drawtext(_T("��  ʼ"), &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

    //�����˳���ť
    setfillcolor(myBLACK);
    solidroundrect(760, 660, 930, 720, 25, 25);
    setlinecolor(myWHITE);
    setlinestyle(PS_SOLID, 3);
    setbkcolor(myBLACK);
    roundrect(764, 664, 926, 716, 20, 20);
    gettextstyle(&f);
    f.lfHeight = 35;
    f.lfQuality = ANTIALIASED_QUALITY;
    _tcscpy_s(f.lfFaceName, _T("΢���ź�"));
    settextstyle(&f);
    settextcolor(myWHITE);
    setbkcolor(myBLACK);
    r = {760, 660, 930, 720};
    drawtext(_T("��  ��"), &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
}

pair<int, int> EasyX::setMode() {
    LOGFONT f;
    RECT r;
    MOUSEMSG m{};
    int temp = 0, firstPlayer = 1, secondPlayer = 1;
    while (true) {
        m = GetMouseMsg();
        switch (m.uMsg) {
            case WM_LBUTTONDOWN:
                //ѡ���������
                if (m.x > 760 && m.x < 930 && m.y > 60 && m.y < 120) {
                    firstPlayer = 1;
                    setfillcolor(myBLACK);
                    solidroundrect(760, 60, 930, 120, 25, 25);
                    gettextstyle(&f);
                    f.lfHeight = 35;
                    f.lfQuality = ANTIALIASED_QUALITY;
                    _tcscpy_s(f.lfFaceName, _T("΢���ź�"));
                    settextstyle(&f);
                    settextcolor(myWHITE);
                    setbkcolor(myBLACK);
                    r = {760, 60, 930, 120};
                    drawtext(_T("��  ��"), &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
                    setfillcolor(myWHITE);
                    solidroundrect(760, 130, 930, 190, 25, 25);
                    setlinecolor(myBLACK);
                    setlinestyle(PS_SOLID, 3);
                    setbkcolor(myWHITE);
                    roundrect(761, 131, 929, 189, 25, 25);
                    gettextstyle(&f);
                    f.lfHeight = 35;
                    f.lfQuality = ANTIALIASED_QUALITY;
                    _tcscpy_s(f.lfFaceName, _T("΢���ź�"));
                    settextstyle(&f);
                    settextcolor(myBLACK);
                    setbkcolor(myWHITE);
                    r = {760, 130, 930, 190};
                    drawtext(_T("A    I"), &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
                }
                    //ѡ��AI����
                else if (m.x > 760 && m.x < 930 && m.y > 130 && m.y < 190) {
                    firstPlayer = 2;
                    setfillcolor(myWHITE);
                    solidroundrect(760, 60, 930, 120, 25, 25);
                    setlinecolor(myBLACK);
                    setlinestyle(PS_SOLID, 3);
                    setbkcolor(myWHITE);
                    roundrect(761, 61, 929, 119, 25, 25);
                    gettextstyle(&f);
                    f.lfHeight = 35;
                    f.lfQuality = ANTIALIASED_QUALITY;
                    _tcscpy_s(f.lfFaceName, _T("΢���ź�"));
                    settextstyle(&f);
                    settextcolor(myBLACK);
                    setbkcolor(myWHITE);
                    r = {760, 60, 930, 120};
                    drawtext(_T("��  ��"), &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
                    setfillcolor(myBLACK);
                    solidroundrect(760, 130, 930, 190, 25, 25);
                    gettextstyle(&f);
                    f.lfHeight = 35;
                    f.lfQuality = ANTIALIASED_QUALITY;
                    _tcscpy_s(f.lfFaceName, _T("΢���ź�"));
                    settextstyle(&f);
                    settextcolor(myWHITE);
                    setbkcolor(myBLACK);
                    r = {760, 130, 930, 190};
                    drawtext(_T("A    I"), &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
                }
                    //ѡ����Һ���
                else if (m.x > 760 && m.x < 930 && m.y > 250 && m.y < 310) {
                    secondPlayer = 1;
                    setfillcolor(myBLACK);
                    solidroundrect(760, 250, 930, 310, 25, 25);
                    gettextstyle(&f);
                    f.lfHeight = 35;
                    f.lfQuality = ANTIALIASED_QUALITY;
                    _tcscpy_s(f.lfFaceName, _T("΢���ź�"));
                    settextstyle(&f);
                    settextcolor(myWHITE);
                    setbkcolor(myBLACK);
                    r = {760, 250, 930, 310};
                    drawtext(_T("��  ��"), &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
                    setfillcolor(myWHITE);
                    solidroundrect(760, 320, 930, 380, 25, 25);
                    setlinecolor(myBLACK);
                    setlinestyle(PS_SOLID, 3);
                    setbkcolor(myWHITE);
                    roundrect(761, 321, 929, 379, 25, 25);
                    gettextstyle(&f);
                    f.lfHeight = 35;
                    f.lfQuality = ANTIALIASED_QUALITY;
                    _tcscpy_s(f.lfFaceName, _T("΢���ź�"));
                    settextstyle(&f);
                    settextcolor(myBLACK);
                    setbkcolor(myWHITE);
                    r = {760, 320, 930, 380};
                    drawtext(_T("A    I"), &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
                }
                    //ѡ��AI����
                else if (m.x > 760 && m.x < 930 && m.y > 320 && m.y < 380) {
                    secondPlayer = 2;
                    setfillcolor(myWHITE);
                    solidroundrect(760, 250, 930, 310, 25, 25);
                    setlinecolor(myBLACK);
                    setlinestyle(PS_SOLID, 3);
                    setbkcolor(myWHITE);
                    roundrect(761, 251, 929, 309, 25, 25);
                    gettextstyle(&f);
                    f.lfHeight = 35;
                    f.lfQuality = ANTIALIASED_QUALITY;
                    _tcscpy_s(f.lfFaceName, _T("΢���ź�"));
                    settextstyle(&f);
                    settextcolor(myBLACK);
                    setbkcolor(myWHITE);
                    r = {760, 250, 930, 310};
                    drawtext(_T("��  ��"), &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
                    setfillcolor(myBLACK);
                    solidroundrect(760, 320, 930, 380, 25, 25);
                    gettextstyle(&f);
                    f.lfHeight = 35;
                    f.lfQuality = ANTIALIASED_QUALITY;
                    _tcscpy_s(f.lfFaceName, _T("΢���ź�"));
                    settextstyle(&f);
                    settextcolor(myWHITE);
                    setbkcolor(myBLACK);
                    r = {760, 320, 930, 380};
                    drawtext(_T("A    I"), &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
                }
                    //�ڿ�ʼ��ť�ϰ�����꣬��ť���
                else if (m.x > 760 && m.x < 930 && m.y > 420 && m.y < 480) {
                    setfillcolor(myBLACK);
                    solidroundrect(760, 420, 930, 480, 25, 25);
                    setlinecolor(myWHITE);
                    setlinestyle(PS_SOLID, 3);
                    setbkcolor(myBLACK);
                    roundrect(764, 424, 926, 476, 20, 20);
                    gettextstyle(&f);
                    f.lfHeight = 35;
                    f.lfQuality = ANTIALIASED_QUALITY;
                    _tcscpy_s(f.lfFaceName, _T("΢���ź�"));
                    settextstyle(&f);
                    settextcolor(myWHITE);
                    setbkcolor(myBLACK);
                    r = {760, 420, 930, 480};
                    drawtext(_T("��  ʼ"), &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
                    temp = 1;
                }
                    //����˳���ť
                else if (m.x > 760 && m.x < 930 && m.y > 650 && m.y < 710) {
                    exit(0);
                }
                break;

            case WM_LBUTTONUP:
                //�ڿ�ʼ��ť���ɿ����
                if (m.x > 760 && m.x < 930 && m.y > 420 && m.y < 480 && temp == 1) {
                    //�������¿�ʼ��ť
                    setfillcolor(myWHITE);
                    solidroundrect(760, 420, 930, 480, 25, 25);
                    setlinecolor(myBLACK);
                    setlinestyle(PS_SOLID, 3);
                    setbkcolor(myWHITE);
                    roundrect(761, 421, 929, 479, 24, 24);
                    roundrect(767, 427, 923, 473, 18, 18);
                    gettextstyle(&f);
                    f.lfHeight = 35;
                    f.lfQuality = ANTIALIASED_QUALITY;
                    _tcscpy_s(f.lfFaceName, _T("΢���ź�"));
                    settextstyle(&f);
                    settextcolor(myBLACK);
                    setbkcolor(myWHITE);
                    r = {760, 420, 930, 480};
                    drawtext(_T("���¿�ʼ"), &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

                    //���ƻ��尴ť
                    setfillcolor(myWHITE);
                    solidroundrect(760, 490, 930, 550, 25, 25);
                    setlinecolor(myBLACK);
                    setlinestyle(PS_SOLID, 3);
                    setbkcolor(myWHITE);
                    roundrect(761, 491, 929, 549, 24, 24);
                    roundrect(767, 497, 923, 543, 18, 18);
                    gettextstyle(&f);
                    f.lfHeight = 35;
                    f.lfQuality = ANTIALIASED_QUALITY;
                    _tcscpy_s(f.lfFaceName, _T("΢���ź�"));
                    settextstyle(&f);
                    settextcolor(myBLACK);
                    setbkcolor(myWHITE);
                    r = {760, 490, 930, 550};
                    drawtext(_T("��  ��"), &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

                    //������ʾ��ť
                    setfillcolor(myWHITE);
                    solidroundrect(760, 560, 930, 620, 25, 25);
                    setlinecolor(myBLACK);
                    setlinestyle(PS_SOLID, 3);
                    setbkcolor(myWHITE);
                    roundrect(761, 561, 929, 619, 24, 24);
                    roundrect(767, 567, 923, 613, 18, 18);
                    gettextstyle(&f);
                    f.lfHeight = 35;
                    f.lfQuality = ANTIALIASED_QUALITY;
                    _tcscpy_s(f.lfFaceName, _T("΢���ź�"));
                    settextstyle(&f);
                    settextcolor(myBLACK);
                    setbkcolor(myWHITE);
                    r = {760, 560, 930, 620};
                    drawtext(_T("��  ʾ"), &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
                    return {firstPlayer, secondPlayer};
                }
                    //��ʼ��ť�ָ���ɫ
                else if (temp == 1) {
                    setfillcolor(myWHITE);
                    solidroundrect(760, 420, 930, 480, 25, 25);
                    setlinecolor(myBLACK);
                    setlinestyle(PS_SOLID, 3);
                    setbkcolor(myWHITE);
                    roundrect(761, 421, 929, 479, 24, 24);
                    roundrect(767, 427, 923, 473, 18, 18);
                    gettextstyle(&f);
                    f.lfHeight = 35;
                    f.lfQuality = ANTIALIASED_QUALITY;
                    _tcscpy_s(f.lfFaceName, _T("΢���ź�"));
                    settextstyle(&f);
                    settextcolor(myBLACK);
                    setbkcolor(myWHITE);
                    r = {760, 420, 930, 480};
                    drawtext(_T("��  ʼ"), &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
                    temp = 0;
                }
        }
    }
}

pair<int, int> EasyX::getMousePos() {
    pair<int, int> pos;
    MOUSEMSG m{};
    while (true) {
        m = GetMouseMsg();
        switch (m.uMsg) {
            case WM_LBUTTONDOWN:
                //����˳���ť
                if (m.x > 760 && m.x < 930 && m.y > 650 && m.y < 710) {
                    exit(0);
                }
                    //������¿�ʼ��ť
                else if (m.x > 760 && m.x < 930 && m.y > 420 && m.y < 480) {
                    return {-1, -1};
                }
                    //������尴ť
                else if (m.x > 760 && m.x < 930 && m.y > 490 && m.y < 550) {
                    return {-2, -2};
                }
                    //�����ʾ��ť
                else if (m.x > 760 && m.x < 930 && m.y > 560 && m.y < 620) {
                    return {-3, -3};
                }
                break;
            case WM_LBUTTONUP:
                //�����������
                if (m.x < 750) {
                    pos.first = m.y / 50 + 1;
                    pos.second = m.x / 50 + 1;
                    return pos;
                }
                break;
        }
    }
}

void EasyX::printPieces(pair<int, int> pos, pair<int, int> prePos, int turn) {
    if (turn == 1) {
        if (prePos.first != -1) {
            setfillcolor(myWHITE);
            solidcircle(50 * prePos.second - 25, 50 * prePos.first - 25, 5);
        }
        setfillcolor(myBLACK);
        solidcircle(50 * pos.second - 25, 50 * pos.first - 25, 23);
        setfillcolor(RED);
        solidcircle(50 * pos.second - 25, 50 * pos.first - 25, 5);
    } else {
        if (prePos.first != -1) {
            setfillcolor(myBLACK);
            solidcircle(50 * prePos.second - 25, 50 * prePos.first - 25, 5);
        }
        setfillcolor(myWHITE);
        solidcircle(50 * pos.second - 25, 50 * pos.first - 25, 23);
        setlinecolor(myBLACK);
        setlinestyle(PS_SOLID, 3);
        circle(50 * pos.second - 25, 50 * pos.first - 25, 22);
        setfillcolor(RED);
        solidcircle(50 * pos.second - 25, 50 * pos.first - 25, 5);
    }
}

void EasyX::undo(int num, int mode, stack<pair<int, int> > record) {
    if (record.empty())
        return;
    pair<int, int> pos;
    for (int i = 0; i < num; ++i) {
        pos = record.top();
        setfillcolor(BKCOLOR);
        solidcircle(50 * pos.second - 25, 50 * pos.first - 25, 24);
        setlinecolor(BLACK);
        if (pos.first > 1 && pos.first < 15 && pos.second > 1 && pos.second < 15) {
            setlinestyle(PS_SOLID, 1);
            line(50 * pos.second - 50, 50 * pos.first - 25, 50 * pos.second, 50 * pos.first - 25);
            line(50 * pos.second - 25, 50 * pos.first - 50, 50 * pos.second - 25, 50 * pos.first);
        } else if (pos.first == 1 && pos.second == 1) {
            setlinestyle(PS_SOLID, 3);
            line(50 * pos.second - 25, 50 * pos.first - 25, 50 * pos.second, 50 * pos.first - 25);
            line(50 * pos.second - 25, 50 * pos.first - 25, 50 * pos.second - 25, 50 * pos.first);
        } else if (pos.first == 1 && pos.second == 15) {
            setlinestyle(PS_SOLID, 3);
            line(50 * pos.second - 50, 50 * pos.first - 25, 50 * pos.second - 25, 50 * pos.first - 25);
            line(50 * pos.second - 25, 50 * pos.first - 25, 50 * pos.second - 25, 50 * pos.first);
        } else if (pos.first == 15 && pos.second == 1) {
            setlinestyle(PS_SOLID, 3);
            line(50 * pos.second - 25, 50 * pos.first - 25, 50 * pos.second, 50 * pos.first - 25);
            line(50 * pos.second - 25, 50 * pos.first - 50, 50 * pos.second - 25, 50 * pos.first - 25);
        } else if (pos.first == 15 && pos.second == 15) {
            setlinestyle(PS_SOLID, 3);
            line(50 * pos.second - 50, 50 * pos.first - 25, 50 * pos.second - 25, 50 * pos.first - 25);
            line(50 * pos.second - 25, 50 * pos.first - 50, 50 * pos.second - 25, 50 * pos.first - 25);
        } else if (pos.first == 1) {
            setlinestyle(PS_SOLID, 3);
            line(50 * pos.second - 50, 50 * pos.first - 25, 50 * pos.second, 50 * pos.first - 25);
            setlinestyle(PS_SOLID, 1);
            line(50 * pos.second - 25, 50 * pos.first - 25, 50 * pos.second - 25, 50 * pos.first);
        } else if (pos.first == 15) {
            setlinestyle(PS_SOLID, 3);
            line(50 * pos.second - 50, 50 * pos.first - 25, 50 * pos.second, 50 * pos.first - 25);
            setlinestyle(PS_SOLID, 1);
            line(50 * pos.second - 25, 50 * pos.first - 50, 50 * pos.second - 25, 50 * pos.first - 25);
        } else if (pos.second == 1) {
            setlinestyle(PS_SOLID, 1);
            line(50 * pos.second - 25, 50 * pos.first - 25, 50 * pos.second, 50 * pos.first - 25);
            setlinestyle(PS_SOLID, 3);
            line(50 * pos.second - 25, 50 * pos.first - 50, 50 * pos.second - 25, 50 * pos.first);
        } else if (pos.second == 15) {
            setlinestyle(PS_SOLID, 1);
            line(50 * pos.second - 50, 50 * pos.first - 25, 50 * pos.second - 25, 50 * pos.first - 25);
            setlinestyle(PS_SOLID, 3);
            line(50 * pos.second - 25, 50 * pos.first - 50, 50 * pos.second - 25, 50 * pos.first);
        }
        if ((pos.first == 4 && pos.second == 4) || (pos.first == 4 && pos.second == 12) || (pos.first == 8 && pos.second == 8) || (pos.first == 12 && pos.second == 4) || (pos.first == 12 && pos.second == 12)) {
            setfillcolor(BLACK);
            solidcircle(50 * pos.second - 25, 50 * pos.first - 25, 3);
        }
        record.pop();
        if (!record.empty()) {
            pos = record.top();
            setfillcolor(RED);
            solidcircle(50 * pos.second - 25, 50 * pos.first - 25, 5);
        }
    }
    if (mode == 2) {
        record.pop();
        int turn = 2 - (int) record.size() % 2;
        while (!record.empty()) {
            pos = record.top();
            if (turn == 1) {
                setfillcolor(myBLACK);
                solidcircle(50 * pos.second - 25, 50 * pos.first - 25, 10);
            } else {
                setfillcolor(myWHITE);
                solidcircle(50 * pos.second - 25, 50 * pos.first - 25, 10);
            }
            record.pop();
            turn = 3 - turn;
        }
    }
}

int EasyX::showWinner(pair<int, int> begin, pair<int, int> end) {
    int dx = (end.first - begin.first) / 4, dy = (end.second - begin.second) / 4;
    for (int i = 0; i < 5; ++i)
        solidcircle(50 * (begin.second + i * dy) - 25, 50 * (begin.first + i * dx) - 25, 5);
    MOUSEMSG m{};
    while (true) {
        m = GetMouseMsg();
        switch (m.uMsg) {
            case WM_LBUTTONDOWN:
                //����˳���ť
                if (m.x > 760 && m.x < 930 && m.y > 650 && m.y < 710) {
                    exit(0);
                }
                    //������¿�ʼ��ť
                else if (m.x > 760 && m.x < 930 && m.y > 420 && m.y < 480) {
                    return -1;
                }
                    //������尴ť
                else if (m.x > 760 && m.x < 930 && m.y > 490 && m.y < 550) {
                    return -2;
                }
                break;
        }
    }
}
