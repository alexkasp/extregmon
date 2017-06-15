using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;
using GUI.ViewModel;
namespace GUI
{
    /// <summary>
    /// Логика взаимодействия для MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        ExtregClient erc;

        public MainWindow()
        {
            InitializeComponent();
            erc = new ExtregClient();
        }

        private void Window_Loaded(object sender, RoutedEventArgs e)
        {
          //  ServerViewModel srv = new ServerViewModel();

            //System.Windows.Data.CollectionViewSource serverViewModelViewSource = ((System.Windows.Data.CollectionViewSource)(this.FindResource("serverViewModelViewSource")));
            // Загрузите данные, установив свойство CollectionViewSource.Source:
            //serverViewModelViewSource.Source = srv;
        }

        private void button_Click(object sender, RoutedEventArgs e)
        {
            string answer = "";
            string message = "";
            if(!erc.connect(ref message))
            {
                MessageBox.Show(message);

            }
            if (erc.recvAnswer(ref answer))
                richTextBox.Document.Blocks.Add(new Paragraph(new Run(answer)));
        }

        private void button1_Click(object sender, RoutedEventArgs e)
        {
            string command = textBox.Text;
            string answer = "";

            if(erc.sendCommand(command, ref answer))
            {
                if(erc.recvAnswer(ref answer))
                    richTextBox.Document.Blocks.Add(new Paragraph(new Run(answer)));
                else
                {

                    MessageBox.Show(answer);
                }
            }
            else {
                MessageBox.Show(answer);
            }
        }
    }
}
 