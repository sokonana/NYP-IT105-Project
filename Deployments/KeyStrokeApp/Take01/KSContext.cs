using Microsoft.EntityFrameworkCore;

namespace Take01;

public class KSContext : DbContext
{
    public DbSet<KeyStrokeDBModel>? keystrokes { get; set; }
    public DbSet<PredictionKeyStrokeDBModel>? authstrokes {get; set;}
    public KSContext() : base()
    {   
    }

    public KSContext(DbContextOptions<KSContext> options) : base(options)
    {
    }

    protected override void OnConfiguring(DbContextOptionsBuilder optionsBuilder)
    {
        optionsBuilder.UseSqlite("Data Source=ks.db");
    }
}
