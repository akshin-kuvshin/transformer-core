// author: Danila "akshin_" Axyonov

using Teigha.Runtime;
using Application = HostMgd.ApplicationServices.Application;

namespace TransformerCore.View
{
    public static class Program
    {
        [CommandMethod("CreateTransformerCore")]
        public static void Main()
        {
            Application.ShowModalDialog(new MainForm());
        }
    }
}
