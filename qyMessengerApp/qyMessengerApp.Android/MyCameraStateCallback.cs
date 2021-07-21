using Android.App;
using Android.Content;
using Android.Hardware.Camera2;
using Android.OS;
using Android.Runtime;
using Android.Views;
using Android.Widget;
using qy;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace qyMessengerApp.Droid
{
    class MyCameraStateCallback : CameraDevice.StateCallback
    {
        private Fragment_dlgTalk_av owner;

        public MyCameraStateCallback(Fragment_dlgTalk_av owner)
        {
            if ( owner == null)
            {
                throw new System.ArgumentNullException("owner");
            }
            this.owner = owner;
        }

        public override void OnOpened(CameraDevice cameraDevice)
        {
            bool bDbg = false;
            string str;

#if DEBUG
            bDbg = true;
#endif
            //
            if (bDbg)
            {
                str = string.Format("MyCamperaStateCallback.OnOpened");
                qyFuncs.showInfo_open(0, null, str);
            }


            //throw new NotImplementedException();
            owner.mCameraDevice = cameraDevice;
            owner.startPreview();
            owner.mCameraOpenCloseLock.Release();
            if ( null != owner.mTextureView )
            {
                owner.configureTransform(owner.mTextureView.Width, owner.mTextureView.Height);
            }

        }

        public override void OnDisconnected(CameraDevice camera)
        {
            //throw new NotImplementedException();
            owner.mCameraOpenCloseLock.Release();
            camera.Close();
            owner.mCameraDevice = null;
        }

        public override void OnError(CameraDevice camera, [GeneratedEnum] CameraError error)
        {
            //throw new NotImplementedException();
            owner.mCameraOpenCloseLock.Release();
            camera.Close();
            owner.mCameraDevice = null;
            //
            //Activity.
        }

    }
}