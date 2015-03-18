unit formopt;

{$mode objfpc}{$H+}

interface

uses
  Classes, SysUtils, FileUtil, Forms, Controls, Graphics, Dialogs, StdCtrls,
  ButtonPanel, Spin;

type
  { TfmOpt }

  TfmOpt = class(TForm)
    ButtonPanel1: TButtonPanel;
    chkCaretVirtual: TCheckBox;
    chkCurCol: TCheckBox;
    chkCurLine: TCheckBox;
    chkGutterBm: TCheckBox;
    chkGutterNum: TCheckBox;
    chkGutterStat: TCheckBox;
    chkGutterEmpty: TCheckBox;
    edCaretTime: TSpinEdit;
    Label8: TLabel;
  private
    { private declarations }
  public
    { public declarations }
  end;

var
  fmOpt: TfmOpt;

implementation

{$R *.lfm}

end.
