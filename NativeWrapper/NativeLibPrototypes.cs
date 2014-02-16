﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;

namespace NativeWrapper
{
    public class NativeLibPrototypes
    {
        // Declares a managed prototype for unmanaged function.
        [DllImport("CoreNativeLibrary.dll")]
        public static extern System.IntPtr AchiveEffectivity();

        [DllImport("CoreNativeLibrary.dll", CallingConvention = CallingConvention.Cdecl)]
        public unsafe static extern uint* GetOperatorsPtr(IntPtr entity);
    }
}