using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;

namespace Application
{
    public partial class Form1 : Form
    {
        #region Constructor

        public Form1()
        {
            InitializeComponent();
        }

        #endregion

        #region Events

        private void Form1_Load(object sender, EventArgs e)
        {
            pictureBox1.ImageLocation = TreeImage;
            pictureBox2.ImageLocation = BImage;
        }

        private void closeToolStripMenuItem_Click(object sender, EventArgs e)
        {
            System.Windows.Forms.Application.Exit();
        }

        #endregion

        #region Properties

        protected string TreeImage
        {
            get 
            {
                return System.Windows.Forms.Application.StartupPath +  "//Images//1arbol.jpg";
            }
        }

        protected string TreeSelectedImage
        {
            get
            {
                return System.Windows.Forms.Application.StartupPath + "//Images//2arbolpadreBselected.jpg";
            }
        }

        protected string TreeAncestorsImage
        {
            get
            {
                return System.Windows.Forms.Application.StartupPath + "//Images//3arbolpadreBancestros.jpg";
            }
        }

        protected string TreeDescImage
        {
            get
            {
                return System.Windows.Forms.Application.StartupPath + "//Images//4arbolpadreBdesc.jpg";
            }
        }

        protected string BImage
        {
            get
            {
                return System.Windows.Forms.Application.StartupPath + "//Images//letrab.jpg";
            }
        }

        #endregion

        private void clearSelectionToolStripMenuItem_Click(object sender, EventArgs e)
        {
            pictureBox1.ImageLocation = TreeImage;
        }

        private void pictureBox1_Click(object sender, EventArgs e)
        {
            pictureBox1.ImageLocation = TreeSelectedImage;
        }

        private void selectDescendantsToolStripMenuItem_Click(object sender, EventArgs e)
        {
            pictureBox1.ImageLocation = TreeDescImage;
        }

        private void selectAncestorsToolStripMenuItem_Click(object sender, EventArgs e)
        {
            pictureBox1.ImageLocation = TreeAncestorsImage;
        }

        private void nodeDetailsToolStripMenuItem_Click(object sender, EventArgs e)
        {
            new NodeDetail().ShowDialog();
        }

        private void pictureBox1_MouseClick(object sender, MouseEventArgs e)
        {
            pictureBox1_Click(sender, null);
        }

        private void nodeDetailsToolStripMenuItem1_Click(object sender, EventArgs e)
        {
            nodeDetailsToolStripMenuItem_Click(null, null);
        }

        private void selectAncestorsToolStripMenuItem1_Click(object sender, EventArgs e)
        {
            selectAncestorsToolStripMenuItem_Click(null, null);
        }

        private void selectDescendantsToolStripMenuItem1_Click(object sender, EventArgs e)
        {
            selectDescendantsToolStripMenuItem_Click(null, null);
        }

        private void clearSelectionToolStripMenuItem1_Click(object sender, EventArgs e)
        {
            clearSelectionToolStripMenuItem_Click(null, null);
        }
    }
}
