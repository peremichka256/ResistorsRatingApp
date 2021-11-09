//---------------------------------------------------------------------------

#ifndef mainH
#define mainH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <math.h>
#include <Math.hpp>
#include <Grids.hpp>
#include <ValEdit.hpp>
#include <Graphics.hpp>
#define EXP 1000000

//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
        TEdit *Edit1;
        TEdit *Edit2;
        TRadioGroup *RadioGroup1;
        TValueListEditor *ValueListEditor1;
        TImage *Image1;
        void __fastcall Edit1Change(TObject *Sender);
        void __fastcall Edit2Change(TObject *Sender);
        void __fastcall RadioGroup1Click(TObject *Sender);
        void __fastcall Edit1Exit(TObject *Sender);
        void __fastcall Edit2Exit(TObject *Sender);
private:
        //���� ������� �������� � ��������� ����������
        double _inputVoltage;
        double _outputVoltage;

        //���� � ������� ������ ��������� ����
        unsigned short _selectedRaw;
        void SetSelectedRaw(unsigned short selectedRaw);
        // User declarations
public:
        //�������
        void SetInputVoltage(double inputVoltage);
        void SetOutputVoltage(double outputVoltage);

        //�������
        double GetInputVoltage();
        double GetOutputVoltage();
        unsigned short GetSelectedRaw();

        void CalculateResistors(); //����� ���������� ���������
        // User declarations
        __fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
