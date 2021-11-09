//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "main.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{
        Edit2->ReadOnly = true;
}

void TForm1::SetSelectedRaw(unsigned short selectedRaw)
{
        _selectedRaw = selectedRaw;
}

void TForm1::SetInputVoltage(double inputVoltage)
 {
        _inputVoltage = inputVoltage;
 }

 void TForm1::SetOutputVoltage(double outputVoltage)
 {
        if(outputVoltage < _inputVoltage)
        {
                _outputVoltage = outputVoltage;
        }
        else throw Exception("¬ыходное напр€жение должно быть меньше входного");
 }

 double TForm1::GetInputVoltage()
 {
        return _inputVoltage;
 }

 double TForm1::GetOutputVoltage()
 {
        return _outputVoltage;
 }

 unsigned short TForm1::GetSelectedRaw()
 {
        return _selectedRaw;
 }

 void TForm1::CalculateResistors()
 {
        //коэффицент отношени€ напр€жений из формулы R1=R2(Uin/Uout-1)
        double coefOfVoltageDifference = (_inputVoltage/_outputVoltage) - 1;

        for (int i = 0; i <= _selectedRaw; i++)
        {
                //поочередно беретс€ каждый номинал из р€да
                /*значение номиналов рассчитываетс€ через дес€тку в степени
                пор€дкового номера из р€да и округл€етс€ до двух знаков*/
                double secondResistorValue =
                        RoundTo((double)Power(10.0,(i /(double)GetSelectedRaw())),-2);

                for(int j = 0; j <= _selectedRaw; j++)
                {
                        /*поочередно из р€да беретс€ каждый номинал и провер€етс€
                        на соответсвие*/
                        double firstResistorValue =
                        RoundTo((double)Power(10.0,(j /(double)GetSelectedRaw())),-2);
                        double resistorRatio =
                                (double)(firstResistorValue/secondResistorValue);
                        int powRatio =
                                ((coefOfVoltageDifference/resistorRatio)*EXP);
                        int multiplier = 1;
                        int higherBitOfReistorValue
                                = secondResistorValue * coefOfVoltageDifference;

                        /* цикл дл€ определени€ пор€дка первого резистора*/
                        while(higherBitOfReistorValue > 10)
                        {
                                multiplier *= 10;
                                powRatio /= 10;
                                higherBitOfReistorValue /= 10;
                        }

                        /*если два номинала дают необходимое значение Uout
                        заносим их в таблицу*/
                        if ((powRatio % EXP == 0)&&(powRatio / EXP == 1)
                                ||(powRatio % EXP == EXP - 1)&&(powRatio / EXP == 0))
                        {
                                if(j % 2 == 0 && i % 2 == 0)
                                {
                                AnsiString secondResistString =
                                        (AnsiString)secondResistorValue
                                        + " (E" + GetSelectedRaw()/2 +")";
                                ValueListEditor1->
                                        InsertRow(firstResistorValue*multiplier,
                                        secondResistString,true);
                                }
                                else
                                {
                                ValueListEditor1->
                                        InsertRow(firstResistorValue*multiplier,
                                        secondResistorValue,true);
                                }

                        }
                }
        }
 }
//---------------------------------------------------------------------------
void __fastcall TForm1::Edit1Change(TObject *Sender)
{
        if(Edit1->Text != "")
        {
                try
                {
                        SetInputVoltage(Edit1->Text.ToDouble());
                }
                catch(...)
                {
                        Edit1->Color = clRed;
                        ShowMessage("Ќеобходимо ввести число");
                }
                Edit2->ReadOnly = false;
        }
        else
        {
                Edit2->ReadOnly = true;
        }
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Edit2Change(TObject *Sender)
{
        if(Edit2->Text != "")
        {
                try
                {
                        SetOutputVoltage(Edit2->Text.ToDouble());
                }
                catch(...)
                {
                        Edit2->Color = clRed;
                        ShowMessage("«начение выходного напр€жени€ должно быть меньше входного");
                }
        }
}
//---------------------------------------------------------------------------


void __fastcall TForm1::RadioGroup1Click(TObject *Sender)
{
        try
        {
                if (RadioGroup1->ItemIndex == 0)
                {
                        SetSelectedRaw(24);
                        ValueListEditor1->Strings->Clear();
                }
                else if (RadioGroup1->ItemIndex == 1)
                {
                        SetSelectedRaw(48);
                        ValueListEditor1->Strings->Clear();
                }
                else if (RadioGroup1->ItemIndex == 2)
                {
                        SetSelectedRaw(96);
                        ValueListEditor1->Strings->Clear();
                }
                else if (RadioGroup1->ItemIndex == 3)
                {
                        SetSelectedRaw(192);
                        ValueListEditor1->Strings->Clear();
                }

                if(ValueListEditor1->RowCount != 0)
                {
                       TForm1::CalculateResistors();
                }
        }
        catch(...)
        {
                ShowMessage("¬ведите напр€жени€");
                RadioGroup1->ItemIndex = -1;
        }
}
//---------------------------------------------------------------------------


void __fastcall TForm1::Edit1Exit(TObject *Sender)
{
        Edit1->Color = clWindow;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Edit2Exit(TObject *Sender)
{
        Edit2->Color = clWindow;
}
//---------------------------------------------------------------------------

