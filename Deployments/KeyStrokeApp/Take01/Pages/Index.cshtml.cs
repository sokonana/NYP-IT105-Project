using Microsoft.AspNetCore.Mvc;
using Microsoft.AspNetCore.Mvc.RazorPages;

namespace Take01.Pages
{
    public class IndexModel : PageModel
    {
        public int TotalKeyStroke {get; set;}
        public IndexModel()
        {
           
        }

        public void OnGet()
        {

        }

        public async Task OnPost(KeyStrokeModel[] uptimes, KeyStrokeModel[] downtimes)
        {
            TotalKeyStroke = uptimes.Length;

            KSContext _context = new KSContext();
            DateTime Updated = DateTime.Now;

            if (uptimes != null && downtimes != null && _context != null && _context.keystrokes != null)
            {
                for(int i = 0; i < downtimes.Length; i++)
                {
                    KeyStrokeDBModel NewItemDn = new KeyStrokeDBModel();
                    KeyStrokeDBModel NewItemUp = new KeyStrokeDBModel();

                    NewItemDn.KeyCode = downtimes[i].keycode;
                    NewItemDn.KeyChar = KeyTool.GetKeyChar(downtimes[i].keycode);
                    NewItemDn.Timestamp = downtimes[i].timestamp;
                    NewItemDn.Type = 0;
                    NewItemDn.UpdatedOn = Updated;

                    try
                    {
                        NewItemUp.KeyCode = uptimes[i].keycode;
                        NewItemUp.KeyChar = KeyTool.GetKeyChar(uptimes[i].keycode);
                        NewItemUp.Timestamp = uptimes[i].timestamp;
                        NewItemUp.Type = 1;
                        NewItemUp.UpdatedOn = Updated;

                        await _context.keystrokes.AddRangeAsync(new KeyStrokeDBModel[] { NewItemDn, NewItemUp });

                    }
                    catch(IndexOutOfRangeException)  // if up keystroke not captured, then skip
                    {
                        await _context.keystrokes.AddAsync(NewItemDn);
                    }


                    
                }

                await _context.SaveChangesAsync();
            }

            
        }

       
    }
}