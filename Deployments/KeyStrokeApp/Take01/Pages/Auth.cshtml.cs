using System.Text;
using System.Text.Json;
using Microsoft.AspNetCore.Mvc;
using Microsoft.AspNetCore.Mvc.RazorPages;
using System.Net.Http.Headers;
using System.Collections.Generic;
using Microsoft.EntityFrameworkCore;

namespace Take01.Pages
{
    public class AuthModel : PageModel
    {
        public string? ErrMsg {get; set;}
        public ResponseModel? Results {get; set;}

        protected List<PredictionKeyStrokeDBModel>? KeyStrokeList { get; set; }
        protected List<KeyPressView>? KeyPressList { get; set; }
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

        public AuthModel()
        {
            KeyStrokeList = new List<PredictionKeyStrokeDBModel>();
            KeyPressList = new List<KeyPressView>();
        }

        public void OnGet()
        {
        }

        public async Task<JsonResult> OnPostMyResult(KeyStrokeModel[] uptimes, KeyStrokeModel[] downtimes)
        {
            // Test Data
            //double[] timing = new double[] {0.111,0.081,0.094,0.069,0.062,0.14,0.071,0.133,0.093,0.271,0.101,0.073,0.081,0.06,0.112,0.029,0.071,0.165,0.051,0.141,0.051}; 
            double[] timing = new double[21];

            // Capture all the timing data here
            KSContext _context = new KSContext();
            DateTime Updated = DateTime.Now;

            // 1) Captured them into the database table first
            if (uptimes != null && downtimes != null && _context != null && _context?.authstrokes != null)
            {
                for(int i = 0; i < downtimes.Length; i++)
                {
                    PredictionKeyStrokeDBModel NewItemDn = new PredictionKeyStrokeDBModel();
                    PredictionKeyStrokeDBModel NewItemUp = new PredictionKeyStrokeDBModel();

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

                        await _context.authstrokes.AddRangeAsync(new PredictionKeyStrokeDBModel[] { NewItemDn, NewItemUp });

                    }
                    catch(IndexOutOfRangeException)  // if up keystroke not captured, then skip
                    {
                        await _context.authstrokes.AddAsync(NewItemDn);
                    }


                    
                }

                await _context.SaveChangesAsync();

                // 2) Read timing data from database table
                var QKeyLatest = from x in _context.authstrokes where x.UpdatedOn == Updated select x;
                if (await QKeyLatest.AnyAsync())
                {
                    int seq = 0;
                    KeyStrokeList = await QKeyLatest.ToListAsync();

                    // Total number of keys are half of total captured for down and up times
                    int TotalSeq = KeyStrokeList.Count() / 2;

                    // Check for last Enter key
                    bool Extra = (KeyStrokeList.Count() % 2) == 1 ? true: false;

                    for (seq = 0; seq < TotalSeq ;  seq++)
                    {
                        // KeyPressList.Add(new KeyPressView
                        // {
                        //     Sequence = seq,
                        //     KeyCode = KeyStrokeList[seq*2].KeyCode,
                        //     KeyHoldInterval = KeyStrokeList[seq * 2 + 1].Timestamp - KeyStrokeList[seq * 2].Timestamp,
                        //     // Check whether this is the last pair. For last pair, there are no more key transfer
                        //     KeyTransferInterval = (seq < TotalSeq - 1) || Extra ? KeyStrokeList[(seq + 1) *2].Timestamp - KeyStrokeList[seq * 2 + 1].Timestamp : 0.0d
                        // });

                        // Validation here 

                        // 3) Now, create an array of double
                        // Holding tming
                        timing[2*seq] = (KeyStrokeList[seq * 2 + 1].Timestamp - KeyStrokeList[seq * 2].Timestamp) / 1000.0d;

                        // Up-to-Down timing
                        if (seq < TotalSeq - 1)
                            timing[2*seq+1] =  (KeyStrokeList[(seq + 1) *2].Timestamp - KeyStrokeList[seq * 2 + 1].Timestamp) / 1000.0d ;

                        
                    }

                    

                }
            }


            // Try calling Python API for classification results
            try
            {
                await CallAPIAsync(timing);

                Console.WriteLine("Results from API - " + Results?.pred_class + " with prediction probability of " + Results?.pred_prob);

                return new JsonResult(Results);
            }
            catch(Exception ex)
            {
                throw new Exception(ex.Message);
            }
            
           
            
        }

        public async Task CallAPIAsync(double[] timing)
        {
            try
            {
                using (HttpClient Client = new HttpClient())
                {
                    // Sample test data for sending
                    //double[] timing = new double[] {0.111,0.081,0.094,0.069,0.062,0.14,0.071,0.133,0.093,0.271,0.101,0.073,0.081,0.06,0.112,0.029,0.071,0.165,0.051,0.141,0.051}; 

                    // Package as a dictionary data type
                    Dictionary<string, double[]> input = new Dictionary<string, double[]>();

                    input.Add("input", timing);

                    MediaTypeHeaderValue Media = new MediaTypeHeaderValue("application/json");
                    var Content = JsonContent.Create<Dictionary<string, double[]>>(input, Media, new JsonSerializerOptions{ PropertyNameCaseInsensitive = true});
                    var CallResponse = await Client.PostAsync("http://localhost:5001/keystroke", Content);

                    var Response = CallResponse.EnsureSuccessStatusCode();
                    
                    if (Response is not null)
                    {
                        Results = await Response.Content.ReadFromJsonAsync<ResponseModel>(new JsonSerializerOptions{ PropertyNameCaseInsensitive = true});
                        
                        if (Results is null)
                        {
                            throw new Exception("Response successful, but content is null");
                        }
                    }
                    else 
                        throw new Exception("Response is null");
                   
                }
            }
            catch(Exception ex)
            {
                ErrMsg = ex.Message;
            }

        }

    }
}
