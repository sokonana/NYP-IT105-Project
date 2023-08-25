using System.ComponentModel.DataAnnotations;

namespace Take01;

public class KeyStrokeModel
{
    public double timestamp { get; set; }
    public int keycode { get; set; }
}

public class KeyStrokeDBModel
{
    [Key]
    public int Id { get; set; }
    public string KeyChar { get; set; } = string.Empty;
    public int KeyCode { get; set; }
    public double Timestamp { get; set; }
    public int Type { get; set; } // down is 0, up is 1
    public DateTime UpdatedOn { get; set; }
}

public class PredictionKeyStrokeDBModel
{
    [Key]
    public int Id { get; set; }
    public string KeyChar { get; set; } = string.Empty;
    public int KeyCode { get; set; }
    public double Timestamp { get; set; }
    public int Type { get; set; } // down is 0, up is 1
    public DateTime UpdatedOn { get; set; }
}

public static class KeyTool
{
    public static string GetKeyChar(int KeyCode)
    {
        if (KeyCode == 13)
            return "RET";
        else if (KeyCode < 48)
            return "*";
        else if (KeyCode < 58)
            return (KeyCode - 48).ToString();
        else if (KeyCode > 90)
        {
            switch (KeyCode)
            {
                case 188:
                    return ",";
                case 189:
                    return "-";
                case 190:
                    return ".";
                case 191:
                    return "/";
                default:
                    return "!";

            }

        }

        else
            return (Convert.ToChar(KeyCode - 65 + 'a')).ToString();
    }
}