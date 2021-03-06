using Android.App;
using Android.Content;
using Android.Media;
using Android.OS;
using Android.Runtime;
using Android.Views;
using Android.Widget;
using Java.Lang;
using Java.Nio;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;


using Java.Util;


//
#if false


import android.media.*;
import android.os.Handler;
import android.os.Looper;
import android.view.Surface;

import java.io.IOException;
import java.nio.ByteBuffer;
import java.util.ArrayDeque;
import java.util.Locale;
import java.util.Queue;

#endif



//
namespace qy.Droid
{
    public class TmpQueue:Java.Util.ArrayDeque
    {
        public TmpQueue(int maxSize):base(maxSize)
        { }

        public bool isEmpty()
        {
            return this.Size()==0;
        }


    }


    /**
     * Simplifies the MediaCodec interface by wrapping around the buffer processing operations.
     */
    public class MediaCodecWrapper
    {

        // Handler to use for {@code OutputSampleListener} and {code OutputFormatChangedListener}
        // callbacks
        private Handler mHandler;


        // Callback when media output format changes.
        public interface OutputFormatChangedListener
        {
            void outputFormatChanged(MediaCodecWrapper sender, MediaFormat newFormat);
        }

        private OutputFormatChangedListener mOutputFormatChangedListener = null;

        /**
         * Callback for decodes frames. Observers can register a listener for optional stream
         * of decoded data
         */
        public interface OutputSampleListener
        {
            void outputSample(MediaCodecWrapper sender, MediaCodec.BufferInfo info, ByteBuffer buffer);
        }

        /**
         * The {@link MediaCodec} that is managed by this class.
         */
        private MediaCodec mDecoder;

        // References to the internal buffers managed by the codec. The codec
        // refers to these buffers by index, never by reference so it's up to us
        // to keep track of which buffer is which.
        private ByteBuffer[] mInputBuffers;
        private ByteBuffer[] mOutputBuffers;

        // Indices of the input buffers that are currently available for writing. We'll
        // consume these in the order they were dequeued from the codec.
        //private Queue<Integer> mAvailableInputBuffers;
        private TmpQueue mAvailableInputBuffers;

        // Indices of the output buffers that currently hold valid data, in the order
        // they were produced by the codec.
        //private Queue<Integer> mAvailableOutputBuffers;
        private TmpQueue mAvailableOutputBuffers;

        // Information about each output buffer, by index. Each entry in this array
        // is valid if and only if its index is currently contained in mAvailableOutputBuffers.
        private MediaCodec.BufferInfo[] mOutputBufferInfo;

        private MediaCodecWrapper(MediaCodec codec)
        {
            mDecoder = codec;
            codec.Start();
            mInputBuffers = codec.GetInputBuffers();
            mOutputBuffers = codec.GetOutputBuffers();
            mOutputBufferInfo = new MediaCodec.BufferInfo[mOutputBuffers.Length];
            mAvailableInputBuffers = (TmpQueue)new TmpQueue(mOutputBuffers.Length);
            mAvailableOutputBuffers = (TmpQueue)new TmpQueue(mInputBuffers.Length);
        }

        /**
         * Releases resources and ends the encoding/decoding session.
         */
        public void stopAndRelease()
        {
            mDecoder.Stop();
            mDecoder.Release();
            mDecoder = null;
            mHandler = null;
        }

        /**
         * Getter for the registered {@link OutputFormatChangedListener}
         */
        public OutputFormatChangedListener getOutputFormatChangedListener()
        {
            return mOutputFormatChangedListener;
        }

        /**
         *
         * @param outputFormatChangedListener the listener for callback.
         * @param handler message handler for posting the callback.
         */
        public void setOutputFormatChangedListener( OutputFormatChangedListener
    
                outputFormatChangedListener, Handler handler)
        {
            mOutputFormatChangedListener = outputFormatChangedListener;

            // Making sure we don't block ourselves due to a bad implementation of the callback by
            // using a handler provided by client.
            mHandler = handler;
            if (outputFormatChangedListener != null && mHandler == null)
            {
                if (Looper.MyLooper() != null)
                {
                    mHandler = new Handler();
                }
                else
                {
                    throw new IllegalArgumentException(
                            "Looper doesn't exist in the calling thread");
                }
            }
        }

        /**
         * Constructs the {@link MediaCodecWrapper} wrapper object around the video codec.
         * The codec is created using the encapsulated information in the
         * {@link MediaFormat} object.
         *
         * @param trackFormat The format of the media object to be decoded.
         * @param surface Surface to render the decoded frames.
         * @return
         */
        public static MediaCodecWrapper fromVideoFormat( MediaFormat trackFormat,
                Surface surface) 
        {
            MediaCodecWrapper result = null;
            MediaCodec videoCodec = null;

            // BEGIN_INCLUDE(create_codec)
            string mimeType = trackFormat.GetString(MediaFormat.KeyMime);

        // Check to see if this is actually a video mime type. If it is, then create
        // a codec that can decode this mime type.
        if (mimeType.Contains("video/")) {
            videoCodec = MediaCodec.CreateDecoderByType(mimeType);
            videoCodec.Configure(trackFormat, surface, null,  0);

        }

        // If codec creation was successful, then create a wrapper object around the
        // newly created codec.
        if (videoCodec != null) {
            result = new MediaCodecWrapper(videoCodec);
}
// END_INCLUDE(create_codec)

return result;
    }


    /**
     * Write a media sample to the decoder.
     *
     * A "sample" here refers to a single atomic access unit in the media stream. The definition
     * of "access unit" is dependent on the type of encoding used, but it typically refers to
     * a single frame of video or a few seconds of audio. {@link android.media.MediaExtractor}
     * extracts data from a stream one sample at a time.
     *
     * @param input A ByteBuffer containing the input data for one sample. The buffer must be set
     * up for reading, with its position set to the beginning of the sample data and its limit
     * set to the end of the sample data.
     *
     * @param presentationTimeUs  The time, relative to the beginning of the media stream,
     * at which this buffer should be rendered.
     *
     * @param flags Flags to pass to the decoder. See {@link MediaCodec#queueInputBuffer(int,
     * int, int, long, int)}
     *
     * @throws MediaCodec.CryptoException
     */
    public bool writeSample( ByteBuffer input,
             MediaCodec.CryptoInfo crypto,
             long presentationTimeUs,
             int flags)  {
    bool result = false;
    int size = input.Remaining();

    // check if we have dequed input buffers available from the codec
    if (size > 0 && !mAvailableInputBuffers.isEmpty())
    {
        int index = (int)mAvailableInputBuffers.Remove();
        ByteBuffer buffer = mInputBuffers[index];

        // we can't write our sample to a lesser capacity input buffer.
        if (size > buffer.Capacity())
        {
#if false
                    throw new MediaCodecWrapper.WriteException(string.Format(Locale.Us,
                    "Insufficient capacity in MediaCodec buffer: "
                        + "tried to write %d, buffer capacity is %d.",
                    input.Remaining(),
                    buffer.Capacity()));
#endif
                    throw new MediaCodecWrapper.WriteException(string.Format(
                    "Insufficient capacity in MediaCodec buffer: "
                        + "tried to write {0}, buffer capacity is {1}.",
                    input.Remaining(),
                    buffer.Capacity()));
       }

                    buffer.Clear();
        buffer.Put(input);

        // Submit the buffer to the codec for decoding. The presentationTimeUs
        // indicates the position (play time) for the current sample.
        if (crypto == null)
        {
            mDecoder.QueueInputBuffer(index, 0, size, presentationTimeUs, (MediaCodecBufferFlags)flags);
        }
        else
        {
            mDecoder.QueueSecureInputBuffer(index, 0, crypto, presentationTimeUs, (MediaCodecBufferFlags)flags);
        }
        result = true;
    }
    return result;
}

private static MediaCodec.CryptoInfo sCryptoInfo = new MediaCodec.CryptoInfo();

/**
 * Write a media sample to the decoder.
 *
 * A "sample" here refers to a single atomic access unit in the media stream. The definition
 * of "access unit" is dependent on the type of encoding used, but it typically refers to
 * a single frame of video or a few seconds of audio. {@link android.media.MediaExtractor}
 * extracts data from a stream one sample at a time.
 *
 * @param extractor  Instance of {@link android.media.MediaExtractor} wrapping the media.
 *
 * @param presentationTimeUs The time, relative to the beginning of the media stream,
 * at which this buffer should be rendered.
 *
 * @param flags  Flags to pass to the decoder. See {@link MediaCodec#queueInputBuffer(int,
 * int, int, long, int)}
 *
 * @throws MediaCodec.CryptoException
 */
public bool writeSample( MediaExtractor extractor,
        bool isSecure,
        long presentationTimeUs,
        int flags)
{
    bool result = false;

    if (!mAvailableInputBuffers.isEmpty())
    {
        int index = (int)mAvailableInputBuffers.Remove();
        ByteBuffer buffer = mInputBuffers[index];

        // reads the sample from the file using extractor into the buffer
        int size = extractor.ReadSampleData(buffer, 0);
        if (size <= 0)
        {
            flags |= (int)MediaCodecBufferFlags.EndOfStream;
        }

        // Submit the buffer to the codec for decoding. The presentationTimeUs
        // indicates the position (play time) for the current sample.
        if (!isSecure)
        {
            mDecoder.QueueInputBuffer(index, 0, size, presentationTimeUs, (MediaCodecBufferFlags)flags);
        }
        else
        {
            extractor.GetSampleCryptoInfo(sCryptoInfo);
            mDecoder.QueueSecureInputBuffer(index, 0, sCryptoInfo, presentationTimeUs, (MediaCodecBufferFlags)flags);
        }

        result = true;
    }
    return result;
}

/**
 * Performs a peek() operation in the queue to extract media info for the buffer ready to be
 * released i.e. the head element of the queue.
 *
 * @param out_bufferInfo An output var to hold the buffer info.
 *
 * @return True, if the peek was successful.
 */
public bool peekSample(MediaCodec.BufferInfo out_bufferInfo)
{
    // dequeue available buffers and synchronize our data structures with the codec.
    update();
    bool result = false;
    if (!mAvailableOutputBuffers.isEmpty())
    {
        int index = (int)mAvailableOutputBuffers.Peek();
        MediaCodec.BufferInfo info = mOutputBufferInfo[index];
        // metadata of the sample
        out_bufferInfo.Set(
                info.Offset,
                info.Size,
                info.PresentationTimeUs,
                info.Flags);
        result = true;
    }
    return result;
}

/**
 * Processes, releases and optionally renders the output buffer available at the head of the
 * queue. All observers are notified with a callback. See {@link
 * OutputSampleListener#outputSample(MediaCodecWrapper, android.media.MediaCodec.BufferInfo,
 * java.nio.ByteBuffer)}
 *
 * @param render True, if the buffer is to be rendered on the {@link Surface} configured
 *
 */
public void popSample(bool render)
{
    // dequeue available buffers and synchronize our data structures with the codec.
    update();
    if (!mAvailableOutputBuffers.isEmpty())
    {
        int index = (int)mAvailableOutputBuffers.Remove();

                //
                uint tid = qyFuncs.myGetCurrentThreadId();
                qyFuncs.traceLog("before ReleaseOutputBuffer");

        // releases the buffer back to the codec
        mDecoder.ReleaseOutputBuffer(index, render);
    }
}

/**
 * Synchronize this object's state with the internal state of the wrapped
 * MediaCodec.
 */
private void update()
{
            int iErr = -1;

    // BEGIN_INCLUDE(update_codec_state)
    int index;

    // Get valid input buffers from the codec to fill later in the same order they were
    // made available by the codec.
    while ((index = mDecoder.DequeueInputBuffer(0)) != (int)MediaCodecInfoState.TryAgainLater)
    {
        mAvailableInputBuffers.Add(index);
    }


    // Likewise with output buffers. If the output buffers have changed, start using the
    // new set of output buffers. If the output format has changed, notify listeners.
    MediaCodec.BufferInfo info = new MediaCodec.BufferInfo();
    while ((index = mDecoder.DequeueOutputBuffer(info, 0)) != (int)MediaCodecInfoState.TryAgainLater)
    {
        switch ((MediaCodecInfoState)index)
        {
            case MediaCodecInfoState.OutputBuffersChanged:
                mOutputBuffers = mDecoder.GetOutputBuffers();
                mOutputBufferInfo = new MediaCodec.BufferInfo[mOutputBuffers.Length];
                mAvailableOutputBuffers.Clear();
                break;
            case MediaCodecInfoState.OutputFormatChanged:
                if (mOutputFormatChangedListener != null)
                {
#if false
                            mHandler.post(new Runnable() {
                            @Override
                            public void run()
                    {
                        mOutputFormatChangedListener
                                .outputFormatChanged(MediaCodecWrapper.this,
                                        mDecoder.getOutputFormat());

                    }
                });
#endif
                            goto errLabel;
                    }
                    break;
default:
                    // Making sure the index is valid before adding to output buffers. We've already
                    // handled INFO_TRY_AGAIN_LATER, INFO_OUTPUT_FORMAT_CHANGED &
                    // INFO_OUTPUT_BUFFERS_CHANGED i.e all the other possible return codes but
                    // asserting index value anyways for future-proofing the code.
                    if (index >= 0)
{
    mOutputBufferInfo[index] = info;
    mAvailableOutputBuffers.Add(index);
}
else
{
    throw new IllegalStateException("Unknown status from dequeueOutputBuffer");
}
break;
            }

        }
            // END_INCLUDE(update_codec_state)

            iErr = 0;
        errLabel:

            return;
    }

    private class WriteException : Throwable
{
        public WriteException( string detailMessage):base(detailMessage)
{
}
    }


}


}