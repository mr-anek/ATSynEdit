//for browser-scroll feature
var
  cBitmapNiceScroll: TBitmap = nil;
const
  cBitmapNiceScrollRadius = 16;
  crNiceScrollNone  = TCursor(-30);
  crNiceScrollUp    = TCursor(-31);
  crNiceScrollDown  = TCursor(-32);
  crNiceScrollLeft  = TCursor(-33);
  crNiceScrollRight = TCursor(-34);

const
  //under Mac don't use Ctrl key, use Meta key as default (e.g. Meta+C, Meta+A)
  ssXControl = {$ifndef darwin} ssCtrl {$else} ssMeta {$endif};


procedure DoClearScrollInfo(var Info: TATSynScrollInfo);
begin
  Info.NPos:= 0;
  Info.NMin:= 0;
  Info.NMax:= 1;
  Info.NPage:= 1;
end;

function IsEqualScrollInfo(const Info1, Info2: TATSynScrollInfo): boolean;
begin
  Result:=
    (Info1.NPos=Info2.NPos) and
    (Info1.NMin=Info2.NMin) and
    (Info1.NMax=Info2.NMax) and
    (Info1.NPage=Info2.NPage);
end;

procedure InitClipboardFormat;
begin
  cATClipboardFormatId:= RegisterClipboardFormat('Application/X-Laz-ATSynEdit-Block');
end;

procedure InitResourcesNicescroll;
begin
  cBitmapNiceScroll:= TBitmap.Create;
  cBitmapNiceScroll.LoadFromResourceName(HInstance, 'ATSYN_MOVE');
  cBitmapNiceScroll.Transparent:= true;

  Screen.Cursors[crNiceScrollNone]:= LoadCursor(HInstance, 'ATSYN_MOVE');
  Screen.Cursors[crNiceScrollUp]:= LoadCursor(HInstance, 'ATSYN_MOVE_U');
  Screen.Cursors[crNiceScrollDown]:= LoadCursor(HInstance, 'ATSYN_MOVE_D');
  Screen.Cursors[crNiceScrollLeft]:= LoadCursor(HInstance, 'ATSYN_MOVE_L');
  Screen.Cursors[crNiceScrollRight]:= LoadCursor(HInstance, 'ATSYN_MOVE_R');
end;

procedure FreeResources;
begin
  FreeAndNil(cBitmapNiceScroll);
end;

function IsDoubleBufferedNeeded: boolean;
begin
  Result:= WidgetSet.GetLCLCapability(lcCanDrawOutsideOnPaint) = LCL_CAPABILITY_YES;
end;


procedure InitMouseActions(var M: TATMouseActions);
  //
  procedure Add(AId: TATMouseActionId; AState: TShiftState);
  begin
    SetLength(M, Length(M)+1);
    M[High(M)].MouseActionId:= AId;
    M[High(M)].MouseState:= AState;
  end;
  //
begin
  SetLength(M, 0);

  Add(cMouseActionClickSimple, [ssLeft]);
  Add(cMouseActionClickRight, [ssRight]);
  Add(cMouseActionClickAndSelBlock, [ssLeft, ssShift]);
  Add(cMouseActionMakeCaret, [ssLeft, ssXControl]);
  Add(cMouseActionMakeCaretsColumn, [ssLeft, ssXControl, ssShift]);
  Add(cMouseActionNiceScrolling, [ssMiddle]);

  Add(cMouseActionClickSimple, [ssLeft, ssAlt]);
  Add(cMouseActionClickSimple, [ssLeft, ssAltGr]);
  Add(cMouseActionClickSimple, [ssLeft, ssAlt, ssXControl]);
  Add(cMouseActionClickSimple, [ssLeft, ssAlt, ssShift]);
  Add(cMouseActionClickSimple, [ssLeft, ssAlt, ssShift, ssXControl]);
end;


function GetMouseActionId(const M: TATMouseActions; State: TShiftState): TATMouseActionId;
var
  i: integer;
begin
  Result:= cMouseActionNone;
  if State=[] then exit;

  for i:= Low(M) to High(M) do
    if M[i].MouseState=State then
      exit(M[i].MouseActionId);
end;

