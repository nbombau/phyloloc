using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using System.Configuration;

namespace Application
{
    public partial class NodeDetail : Form
    {
        public NodeDetail()
        {
            InitializeComponent();
        }

        private void NodeDetail_Load(object sender, EventArgs e)
        {
            label1.Text = ConfigurationManager.AppSettings[0];
            label2.Text = ConfigurationManager.AppSettings[1];
            label3.Text = ConfigurationManager.AppSettings[2];
            label4.Text = ConfigurationManager.AppSettings[3];
            label5.Text = ConfigurationManager.AppSettings[4];
            label6.Text = ConfigurationManager.AppSettings[5];
            label7.Text = ConfigurationManager.AppSettings[6];
        }
    }
}
