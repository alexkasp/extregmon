using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;


namespace GUI.ViewModel
{
    class ServerViewModel
    {

        public ObservableCollection<ExtregClient> servers { get; set; }
        private ExtregClient refSelectedServer;
        public ExtregClient selectedServer
        {
            get {
                    return refSelectedServer;

            }
            set {
                refSelectedServer = value;
            }
        }

        public void getSelected(out ExtregClient selected)
        {
            selected = refSelectedServer;
        }

        public ServerViewModel()
        {

            servers = new ObservableCollection<ExtregClient>();
            servers.Add(new ExtregClient("212.193.100.94","extreg03"));
            servers.Add(new ExtregClient("212.193.100.95","extreg04"));
            servers.Add(new ExtregClient("212.193.100.96","extreg05"));
            servers.Add(new ExtregClient("212.193.100.97","extreg07"));

            selectedServer = servers.ElementAt<ExtregClient>(0);
        }
      
    }
}
