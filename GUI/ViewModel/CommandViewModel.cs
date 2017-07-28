using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Collections.ObjectModel;

namespace GUI.ViewModel
{

    class CommandViewModel
    {
        public ObservableCollection<commandRule> commands { get; set; }
        public commandRule selectedCmd {get;set;}

        public string fomratSelectedCmd(string param,string param1)
        {
            return selectedCmd.cmtext +param+ "\",\"RequestTime\":\"" + param1 + "\"}";
        }
       public CommandViewModel()
        {
            commands = new ObservableCollection<commandRule>();
            commands.Add(new commandRule("linestatus","{\"Command\":\"LineStatus\",\"LineStatusLogin\":\""));
            commands.Add(new commandRule("getsiplogs","{\"Command\":\"GetSipLogs\",\"LineSipLogLogin\":\""));
            commands.Add(new commandRule("startlogcmd","{\"Command\":\"StartSipLogs\",\"FakeParam\":\""));
            commands.Add(new commandRule("ErrorSearch", "{\"Command\":\"ErrorSearch\",\"LineSipLogLogin\":\""));
            commands.Add(new commandRule("getCalls", "{\"Command\":\"getCalls\",\"LineSipLogLogin\":\""));
            commands.Add(new commandRule("getCallLogPartial", "{\"Command\":\"getCallLogPartial\",\"ChannelSignature\":\""));
            commands.Add(new commandRule("getCallLogFull", "{\"Command\":\"getCallLogFull\",\"ChannelSignature\":\""));
            commands.Add(new commandRule("getCallLogPartialPosition", "{\"Command\":\"getCallLogPartialPosition\",\"ChannelSignature\":\""));
            selectedCmd = commands.ElementAt<commandRule>(0);
       }
    }
}
