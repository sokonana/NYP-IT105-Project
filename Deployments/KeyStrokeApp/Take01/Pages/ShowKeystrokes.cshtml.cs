using System.Security.Cryptography.X509Certificates;
using System.Text;
using System.Xml.Schema;
using Microsoft.AspNetCore.Mvc;
using Microsoft.AspNetCore.Mvc.RazorPages;
using Microsoft.EntityFrameworkCore;
using System.IO;

namespace Take01.Pages;

public class ShowKeystrokesModel : PageModel
{
    [BindProperty]
    public String Subject {get; set;} = string.Empty;

    public string? DebugMsg {get; set;}
    public class KeyPressView
    {
        public int Sequence { get; set; }
        public int KeyCode { get; set; }
        public double KeyHoldInterval { get; set; }
        public double KeyTransferInterval { get; set; }
        public string KeyChar { get {
                return KeyTool.GetKeyChar(KeyCode);
            } }
    }
    protected List<KeyStrokeDBModel>? KeyStrokeList { get; set; }

    public List<KeyPressView>? KeyPressList { get; set; }

    public async Task OnGet()
    {
        KSContext _context = new KSContext();

        if (_context != null )
        {
            KeyPressList = new List<KeyPressView>();

            var QLatestTS = from x in _context.keystrokes select x.UpdatedOn;

            if (await QLatestTS.AnyAsync())
            {

                var LatestTS = (from x in _context.keystrokes select x.UpdatedOn).Max();
                var QKeyStrokes = from x in _context.keystrokes where x.UpdatedOn == LatestTS orderby x.Id select x;
                
                if (await QKeyStrokes.AnyAsync())
                {
                    int seq = 0;
                    KeyStrokeList = await QKeyStrokes.ToListAsync();

                    int TotalSeq = KeyStrokeList.Count() / 2;

                    // Check for last Enter key
                    bool Extra = (KeyStrokeList.Count() % 2) == 1 ? true: false;

                    for (seq = 0; seq < TotalSeq ;  seq++)
                    {
                        KeyPressList.Add(new KeyPressView
                        {
                            Sequence = seq,
                            KeyCode = KeyStrokeList[seq*2].KeyCode,
                            KeyHoldInterval = KeyStrokeList[seq * 2 + 1].Timestamp - KeyStrokeList[seq * 2].Timestamp,
                            // Check whether this is the last pair. For last pair, there are no more key transfer
                            KeyTransferInterval = (seq < TotalSeq - 1) || Extra ? KeyStrokeList[(seq + 1) *2].Timestamp - KeyStrokeList[seq * 2 + 1].Timestamp : 0.0d
                        });
                        
                    }
                }

            }

        }
    }

    public async Task<ActionResult>? OnPostExtractAsync()
    {
        KSContext _context = new KSContext();

        if (_context is not null)
        {
            // Query for all the reps for this session
            var QRepList = from x in _context.keystrokes 
                            group x by x.UpdatedOn into rep
                            orderby rep.Key
                            select rep.Key;

            if (await QRepList.AnyAsync())
            {
                List<DateTime> Rep = await QRepList.ToListAsync();
                List<string> FileContents = new List<string>();
                

                // Forming heading for csv contents
                FileContents.Add("subject,H.period,UD.period.t,H.t,UD.t.i,H.i,UD.i.e,H.e,UD.e.five,H.five,UD.five.Shift.r,H.Shift.r,UD.Shift.r.o,H.o,UD.o.a,H.a,UD.a.n,H.n,UD.n.l,H.l,UD.l.Return,H.Return");

                // Iterate thru each rep to get each keystroke data
                foreach(DateTime r in Rep)
                {
                    
                    var QKeyList = from x in _context.keystrokes where x.UpdatedOn == r orderby x.Id select x;

                    if (await QKeyList.AnyAsync())
                    {
                        var KeyList = await QKeyList.ToListAsync();
                        double[] Row = new double[21];

                        try
                        {
                            StringBuilder RowContents = new StringBuilder();
                            // Validate that the total count is correct first
                            if (KeyList.Count() == 22)
                            {
                                // Get H.period
                                KeyStrokeDBModel? Down = KeyList.Find(x => x.KeyChar == "." && x.Type == 0);
                                KeyStrokeDBModel? Up = KeyList.Find(x => x.KeyChar == "." && x.Type == 1);;

                                List<string> KeyString = new List<string> {
                                         "t", "i", "e", "5", "r", "o", "a", "n", "l","RET"
                                };

                                int num=0;

                                if (Down != null && Up != null)
                                {
                                    // First Hold time for "."
                                    Row[num++] =  (Up.Timestamp - Down.Timestamp) / 1000.0d;

                                    foreach(string keych in KeyString)
                                    {
                                        // UD time
                                        Down = KeyList.Find(x => x.KeyChar == keych && x.Type == 0);
                                        if (Down != null)
                                        {
                                            Row[num] = (Down.Timestamp - Up.Timestamp) / 1000.0d;
                                            num++;
                                        }
                                        else
                                            throw new Exception("Cannot find key");

                                        // Hold time
                                        Up = KeyList.Find(x => x.KeyChar == keych && x.Type == 1);
                                        if (Up != null)
                                        {
                                            Row[num] = (Up.Timestamp - Down.Timestamp) / 1000.0d;
                                            num++;
                                        }
                                        else
                                            throw new Exception("Cannot find key");
    
                                    }

                                    // End of search, collect array of doubles and form a string
                                    string RowStr = string.Join(',', Row);

                                    RowContents.Append(Subject);
                                    RowContents.Append(",");
                                    RowContents.Append(RowStr);
                                    
                                    FileContents.Add(RowContents.ToString());

                                }
                                else
                                {
                                    throw new Exception("Cannot find key");
                                }

                                
                            }
                            else
                                throw new Exception("Key count incorrect");
                        }
                        catch(Exception)
                        {
                            // skip, move to next one
                        }
                    }
                }

                DebugMsg = "File exported for " + Subject + ". Total records: " + QRepList.Count().ToString();
                //DebugMsg = FileContents.ToString();
                
                // Export to file
                string FileName =  Subject + ".csv";
                await System.IO.File.WriteAllLinesAsync("./wwwroot/" + FileName, FileContents);

                return File(FileName, "text/csv");
            }
        }

        return Page();
    }
}
